#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"
#include <iostream>

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
            
        Matrix(){
            hRows = NULL;
            hColumns = NULL;
            columns = 0;
            rows = 0;
        }

        Matrix(int sizeX, int sizeY)
        {
            rows = sizeX;
            columns = sizeY;

            Node<T>* fila = new Node<T>(0,0,sizeX-1,NULL,NULL);
            Node<T>* columna = new Node<T>(0,0,sizeY-1,NULL,NULL);

            for(int i = 0; i < rows-1;i++)
            {
                Node<T>* temp = fila;
                fila = new Node<T>(rows,columns,rows-2-i,NULL,temp);
            }
            hRows = fila;

            for(int i = 0; i < columns-1;i++)
            {
                Node<T>* temp = columna;
                columna = new Node<T>(rows,columns,columns-2-i,temp,NULL);
            }
            hColumns = columna;            
        }

        void set(int x, int y, T data)
        {
            Node<T>* temp1 = hRows;
            Node<T>* temp2 = hColumns;
            
            if(x > rows || y > columns)
                throw "out of range";

            while(temp1->data != x)
                temp1 = temp1->down;

            while(temp2->data != y)
                temp2 = temp2->next;
            
            Node<T>* current2 = temp2;    
            Node<T>* prev2;    
            if(temp1->next == NULL)
            {
                if(data == 0)
                {
                    return;
                }

                else if(temp2->down == NULL)
                {
                    Node<T>* temp = new Node<T>(x,y,data,NULL,NULL);
                    temp1->next = temp;
                    temp2->down = temp;
                }
                else
                {
                    while(current2->down != NULL)
                    {
                        prev2 = current2;
                        current2 = current2->down;

                        if(current2->x > x)
                        {
                            Node<T>* neonode = new Node<T>(x,y,data,NULL,current2);
                            prev2->down = neonode;
                            temp1->next = neonode;
                            return;
                        }
                    }   
                    Node<T>* neonode = new Node<T>(x,y,data,NULL,NULL);
                    current2->down = neonode;
                    temp1->next = neonode;
                }
                
            }
            else
            {
                Node<T>* current1 = temp1;
                Node<T>* prev1;
                while(current1->next != NULL)
                {
                    prev1 = current1;
                    current1 = current1->next;
                    if(current1->y == y)
                    {
                        if(data == 0)
                        {
                            while(current2->down != NULL)
                            {
                                prev2 = current2;
                                current2 = current2->down;

                                if(current2->x == x)
                                {
                                    break;
                                }
                            }
                            prev2->down = current2->down;
                            prev1->next = current1->next;  
                            delete current1;           
                        }
                        else{
                            current1->data = data;    
                        }
                        return;
                    }
                    if(current1->y > y)
                    {
                        if(data == 0)
                        {
                            return;
                        }
                        
                        Node<T>* neonode = new Node<T>(x,y,data,current1,NULL);
                        prev1->next = neonode;

                        if(temp2->down == NULL)
                            temp2->down = neonode;
                            
                        while(current2->down != NULL)
                        {
                            prev2 = current2;
                            current2 = current2->down;

                            if(current2->x > x)
                            {
                                prev2->down = neonode;
                                neonode->down = current2;
                                return;
                            }
                        }            
                        current2->down = neonode;
                        return;
                    }
                }
                    
                if(data == 0)
                {
                    return;
                }

                Node<T>* neonode = new Node<T>(x,y,data,NULL,NULL);
                current1->next = neonode;
                if(temp2->down == NULL)
                {
                    temp2->down = neonode;
                    return;
                }

                while(current2->down != NULL)
                {
                    prev2 = current2;
                    current2 = current2->down;

                    if(current2->x > x)
                    {
                        prev2->down = neonode;
                        neonode->down = current2;
                        return;
                    }
                }
                current2->down = neonode;
            }
        } 
        void Remover(int x, int y)
        {
            set(x,y,0);
        }

        T operator()(int x, int y)
        {
            if(x > rows || y > columns)
                throw "Fuera de límite";

            Node<T>* temp1 = hRows;
                
            while(temp1->data != x)
                temp1 = temp1->down;

            Node<T>* current = temp1;
            while(current->next != NULL)
            {
                current = current->next;
                if(current->y == y)
                    return current->data;
                else if(current->y > y)
                    return 0;
            }
            return 0;
        }

        Matrix<T> operator*(Matrix<T> other){
            if(columns != other.rows)
                throw "diferentes filas y columnas";

            Matrix resultante(rows,other.columns);
            int sum;
            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < other.columns; ++j)
                {
                    sum = 0;
                    for (int k = 0; k < columns ; ++k)
                    {
                        sum += (*this)(i,k)*other(k,j);
                    }
                    resultante.set(i,j,sum);
                }
            }
            return resultante;
        }

        Matrix<T> operator*(T scalar){
            Matrix resultante(rows, columns);
            Node<T>* temp1 = hRows;
            Node<T>* current;
            for (int i = 0; i < rows; ++i)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    resultante.set(current->x,current->y,current->data*scalar);
                    current = current->next;
                }
                temp1 = temp1->down;
            }
            return resultante;
        }

        Matrix<T> operator+(Matrix<T> other){
            if(rows != other.rows || columns != other.columns)
                throw "matrixes of different size";
            
            Matrix resultante(rows,columns);
            resultante = other;
            
            Node<T>* temp1 = hRows;
            Node<T>* current;
            for(int i = 0; i < rows;i++)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    resultante.set(current->x,current->y,current->data + resultante(current->x,current->y));
                    current = current->next;
                }
                temp1 = temp1->down;
            }
            return resultante; 
        }

        Matrix<T> operator-(Matrix<T> other){
            if (rows != other.rows || columns != other.columns)
                throw "las matrices son diferentes";
             
            Matrix resultante(rows,columns);
            resultante = *this;

            Node<T>* temp1 = other.hRows;
            Node<T>* current;   
            for (int i = 0; i < rows; ++i)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    resultante.set(current->x,current->y,resultante(current->x,current->y)-current->data);
                    current = current->next;
                }
                temp1 = temp1->down;
            }
            return resultante;    
        }

        Matrix<T> transposed(){
            Matrix tranpuesta(columns, rows);
            Node<T>* temp1 = hRows;
            Node<T>* current;
            for (int i = 0; i < rows; ++i)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    tranpuesta.set(current->y,current->x,current->data);
                    current = current->next;
                }
                temp1 = temp1->down;
            }
            return tranpuesta;

        }

        Matrix<T> operator=(Matrix<T> other)
        {   
            Node<T>* temp1 = hRows;
            Node<T>* current;
            Node<T>* temp;

            if(rows != other.rows || columns != other.columns)
                throw "las matrices son de tamaños diferentes";

            for(int i = 0; i < rows;i++)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    temp = current;
                    current = current->next;
                    delete temp;
                }
                temp1 = temp1->down;
            }

            temp1 = other.hRows;
            for(int i = 0; i < other.rows;i++)
            {
                current = temp1->next;
                while(current != NULL)
                {
                    set(current->x,current->y,current->data);
                    current = current->next;
                }
                temp1 = temp1->down;
            }
            return *this;
        }
        ~Matrix(){
        }
};

#endif