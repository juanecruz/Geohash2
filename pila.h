#include <iostream>
using namespace std;
template <typename T> class Nodo {
private:
  T dato;
  Nodo *next;

public:
  Nodo(T d) {
    dato = d;
    next = NULL;
  }
  ~Nodo() {}
  T get_dato() { return dato; }
  Nodo *get_next() { return next; }
  void set_dato(T d) { dato = d; }
  void set_next(Nodo *n) { next = n; }
};

template <typename T> class Pila {
private:
  Nodo<T> *ptr;
  int size;

public:
  Pila() {
    ptr = NULL;
    size = 0;
  }
  ~Pila() {
    Nodo<T> *temp = ptr;
    if (ptr != NULL) {
      Nodo<T> *temp_next = ptr->get_next();
      while (temp_next != NULL) {
        delete temp;
        temp = temp_next;
        temp_next = temp->get_next();
      }
      delete temp; // Borrar el último nodo
    }
  }
  void push(T d) {
    Nodo<T> *nodo = new Nodo<T>(d);
    if (ptr == NULL) { // La lista está vacía
      ptr = nodo;
    } else { // La lista no está vacía
      Nodo<T> *temp = ptr;
      nodo->set_next(temp);
      ptr = nodo;
    }
  }
  Nodo<T> *pop() {
    if (ptr == NULL) { // La lista está vacía
      return NULL;
    } else { // La lista no está vacía
      Nodo<T> *to_return = new Nodo<T>((ptr->get_dato()));
      Nodo<T> *temp = ptr->get_next();
      delete ptr;
      ptr = temp;
      return to_return;
    }
  }
  T peak() {
    if (ptr == NULL) { // La lista está vacía
      return NULL;
    } else { // La lista no está vacía
      return ptr->get_dato();
    }
  }
  void print() {
    if (ptr == NULL) { // La lista está vacía
      cout << "La pila está vacía" << endl;
    } else { // La lista no está vacía
      Nodo<T> *temp = ptr;
      cout << "TU PILA: " << endl;
      while (temp != NULL) {
        cout << temp->get_dato() << "\t";
        temp = temp->get_next();
      }
      cout << endl << endl;
      ;
    }
  }
};
