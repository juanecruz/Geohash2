#include <iostream>
#include <random>
#include <cmath>
#include "pila.h"
using namespace std;
long binary_to_decimal(string num) {
  long peso = 1;
  long resultado = 0;
  long num_size = num.length();
  for (long i = num_size - 1; i >= 0; i--) {
    if (num[i] == '1') {
      resultado += peso;
    }
    peso *= 2;
  }
  return resultado;
}
string binary_to_b32(string num) {
  char digits[33] = "0123456789bcdefghjkmnpqrstuvwxyz";
  long x = binary_to_decimal(num);
  string resultado;
  if (x < 32) {
    return resultado + digits[x];
  } else {
    resultado = resultado + digits[x % 32];
    while (x / 32 > 32) {
      x /= 32;
      resultado = digits[x % 32] + resultado;
    }
    return digits[(x / 32) % 32] + resultado;
  }
}
string codificar(float lat, float lon) {
  float lim_inf = -90;
  float lim_sup = 90;
  float lim_izq = -180;
  float lim_der = 180;
  string code = "";
  float avg = 0;
  float avg2 = 0;
  while (code.size() < 40) {
    avg = (lim_inf + lim_sup) / 2;
    avg2 = (lim_izq + lim_der) / 2;
    if (lon >= avg2) {
      code = code + '1';
      lim_izq = avg2;
    } else {
      code = code + '0';
      lim_der = avg2;
    }
    if (lat >= avg) {
      code = code + '1';
      lim_inf = avg;
    } else {
      code = code + '0';
      lim_sup = avg;
    }
  }
  return binary_to_b32(code);
}
class Tuple{
  private:
  double lat;
  double lon;
  string  hash;
  public:
  Tuple(){}
  Tuple(double lt, double lg, string cod){
    lat = lt; lon = lg; hash = cod;
  }
  ~Tuple(){}
  double get_lat(){return lat;}
  double get_lon(){return lon;}
  string get_hash(){return hash;}
  string to_string() {return "("+std::to_string(lat) + "," + std::to_string(lon)+ "," + (hash) + ")";}
  friend std::ostream& operator<<(std::ostream& os, Tuple b) {return os << b.to_string();}
};
class Node{
  private:
  Node* izq;
  Node* der;
  Tuple dato;
  public:
  Node(Tuple coor){
    izq = NULL;
    der = NULL;
    dato = coor;
  }
  ~Node(){}
  Node* get_izq(){return izq;}
  Node* get_der(){return der;}
  void set_der(Node* a){der = a;}
  void set_izq(Node* a){izq = a;}
  Tuple get_dato(){return dato;}
  bool is_hoja(){
    if (der == NULL && izq == NULL){
      return true;
    }else{
      return false;
    }
  }
};
bool comparar(){ //Sergio
  return true;
}
class BinarySearchTree{
  private:
  Node* root;
  public:
  BinarySearchTree(){root = NULL;}
  ~BinarySearchTree(){}
  int max(int a, int b){
    if(a >= b){
      return a;
    }else{
      return b;
    }
  }
  void add(Tuple a, Node* x){
    if (root == NULL){
      root = new Node(a);
    }else{
      if (x->get_dato().get_hash() > a.get_hash()){
        if(x->get_izq() == NULL){
          x->set_izq(new Node(a));
        }else{
          add(a, x->get_izq());
        }
      }else{
        if(x->get_der() == NULL){
          x->set_der(new Node(a));
        }else{
          add(a, x->get_der());
        }
      }
    }
  }
  void add(Tuple a){add(a,root);}
  void print_postorder(Node* x){
        if(x != NULL){
            print_postorder(x->get_izq());
            print_postorder(x->get_der());
            cout<<x->get_dato()<<endl;
        }
  }
  void print_postorder(){print_postorder(root);}
  int height(Node* x){
    if(x->is_hoja()){
        return 0;
    }else{
        int max = -1;
        if(x->get_izq() != NULL){
            max = height(x->get_izq());
        }
        if(x->get_der() != NULL){
            int temp = height(x->get_der());
            if(max < temp){max = temp;}
        }
        return max+1;
    }
  }
  int height(){return height(root);}
  void deep_first(Node* x, string prefix){
    Node* estado = x;
    Pila<Node*> pila;
    pila.push(estado);
    while(pila.peak() != NULL){
      estado = pila.pop()->get_dato();
      if(prefix == estado->get_dato().get_hash().substr(0,4)){
        cout<<estado->get_dato()<<endl;
      }
      if(estado->get_der() != NULL){
        pila.push(estado->get_der());
      }
      if(estado->get_izq() != NULL){
        pila.push(estado->get_izq());
      }
    }
  }
  void deep_first(){deep_first(root,"d2g6");}
  void singleRotation(Node* x, string side){
    Node* temp;
    if(side == "l"){
      temp = x->get_izq()->get_der();
      x->get_izq()->set_der(x);
      x->set_izq(temp);
    }else{
      x->get_der()->set_izq(x);
      x->set_der(temp);
    }
  }
  void search(){
    
  }
};
int main(){ 
  BinarySearchTree t;
  random_device rd;
  default_random_engine generator(rd());
  uniform_real_distribution<double> distributionX(-74.00439955, -74.24726596);
  uniform_real_distribution<double> distributiony(4.48678121,4.78798027);
  double y,x = 0;
  string code;
  for(int i = 0; i < 500000; i++){
     x = distributionX(generator);
     y = distributiony(generator);
     code = codificar(y,x);
     cout<<Tuple(y,x,code)<<endl;
     t.add(Tuple(y,x,code));
  }
  // cout<<"------------------------------"<<endl;
  // t.print_postorder();
  cout<<"------------------------------"<<endl;
  // t.r();
  t.deep_first();
  return 0;
}