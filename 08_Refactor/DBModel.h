/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   DBModel.h
 * Author: hanne
 *
 * Created on April 5, 2024, 5:46 PM
 */

#ifndef DBMODEL_H
#define DBMODEL_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// Constants

const short unsigned int MAXFLD = 81;

template <class T>
class DBModel {
    public:
        
        // Ducktyping safety (enforce T has a `.display` method or don't compile)
        // Wasn't covered in the book or lessons, had to look up how to do this.
        template <typename U = T>
        static auto check_display(int) -> decltype(declval<U>().display(), true_type{});
        template <typename U = T>
        static false_type check_display(...);

        static constexpr bool has_display = decltype(check_display(0))::value;
        
        // Member variables
        string fname;
        fstream file;
        
        // Member functions
        
        DBModel(string fname)
        {
            this->fname = fname;
        }
        
        /// @brief Open file stream.
        void open()
        {
            file.open(fname, std::ios::binary | std::ios::in | std::ios::out);
            if (!file)
            {
                cout << "Error opening file: " << fname << std::endl;
            }
        }
        
        /// @brief Close file stream.
        void close()
        {
            file.close();
        }
        
        /// @brief Create a new database.
        /// @param fname The path to the new database.
        static void create(string fname)
        {

            // check file existence, create if doesn't exist
            fstream file;
            file.open(fname, ios::in | ios::binary);
            if (!file)
            {
                file.close();
                file.open(fname, ios::out | ios::binary);
            }
            else
            {
                cout << "File \"" << fname << "\" already exists.\n";
            }
            file.close();
        }
        
        /// @brief Get the number of records in the database.
        /// @return The number of records in the database.
        int count() {
    
            // Get size of file
            int fbytes = size();

            // Get size of record
            int rbytes = sizeof(T);

            // Calculate and return number of records in database
            return fbytes / rbytes;
        }
        
        /// @brief Get the size (in bytes) of the database.
        /// @return The size (in bytes) of the database.
        long int size() {
            file.seekg(0L, ios::end);
            return file.tellg();
        }
        
        /// @brief Find a record in the database.
        /// @param id The id of the record to find.
        /// @return The index position of the record in the database.
        int find(string id)
        {
            int i = 0;
            int pos = -1;
            int end = count();
            T* record = nullptr;
        //    cout << "Searching for " << email << "\n";  //DEBUG

            while (i < end) {
        //        cout << "Searching record #" << i << "\n";  //DEBUG
                record = get(i);
                if (record->id == id) {  //account found
                    pos = i;
                    break; 
                }
                i++;
            }
            return pos;
        }
        
        /// @brief Add a new record to the database.
        /// @param record The record to add. 
        void add(const T* record)
        {
            file.seekp(0L, ios::end);
            file.write(reinterpret_cast<const char*>(record), sizeof(T));
            file.flush();
        }
        
        /// @brief Get a record from the database.
        /// @param pos The index position of the record to get.
        /// @return The found record. WARNING: Returns dynamically allocated memory.
        T* get(int pos)
        {
            T* record = new T;

            long int cur = pos * sizeof(T);
            file.seekg(cur, ios::beg);
            file.read(reinterpret_cast<char*>(record), sizeof(T));
            return record;
        }
        
        /// @brief Get all records from the database.
        /// @return A pointer to an array of records. WARNING: Returns dynamically allocated memory.
        T* getAll()
        {
            int cnt = count();
            T* records = new T[cnt];
            file.seekg(0L, ios::beg);
            for (int i = 0; i < cnt; i++){
                file.read(reinterpret_cast<char*>(&records[i]), sizeof(T));
            }
            return records;
        }
        
        /// @brief Set the given record at the given index in the database.
        /// @param  pos The index position of the record to set.
        /// @param  pos The record to set.
        void set(int pos, const T* record)
        {
            long int cur = pos * sizeof(T);
            file.seekp(cur, ios::beg);
            file.write(reinterpret_cast<const char*>(record), sizeof(T));
            file.flush();
        }
        
        void del(int pos)
        {
            // Start position of chunk
            long int sbytes = pos * sizeof(T);  //Start byte of record to del.
            long int ebytes = size();  //Size (bytes) of file
            long int rbytes = sizeof(T);  //Size (bytes) of record
            long int cbytes = ebytes - sbytes - rbytes; //Size (bytes) of chunk to shift

            char buffer_a[sbytes];
            char buffer_b[cbytes];
            // Read the chunk of bytes up to record to be deleted into buffer
            file.seekg(0L, ios::beg);
            file.read(buffer_a, sbytes);
            // Read the chunk of bytes after record to be deleted into the buffer
            file.seekg(sbytes + rbytes, ios::beg);
            file.read(buffer_b, cbytes);

            // Clear file contents;
            delAll();

            // Reconstruct file contents (without deleted record)
            file.seekp(0L, ios::end);
            file.write(buffer_a, sbytes);
            file.write(buffer_b, cbytes);

            file.flush();    
        }
        
        /// @brief Delete the record at the given index in the database.
        /// @param pos The index position of the record to delete.
        void delAll(){
    
            // Check if stream is open, close if open, remember initial state
            bool opn = false;
            if (file.is_open()){
                opn = true;
                close();
            }

            // Clear all contents from file
            file.open(fname, ios::binary | ios::out | ios::trunc);
            close();

            // If initial state was open, reopen.
            if (opn) {
                open();
            }
        }
        
        void display() {
            int cnt = count();
            T record;
            file.seekg(0L, ios::beg);
            for (int i = 0; i < cnt; i++){
                file.read(reinterpret_cast<char*>(&record), sizeof(T));
                record.display();
                cout << "\n";
            }
        }
};

#endif /* DBMODEL_H */

