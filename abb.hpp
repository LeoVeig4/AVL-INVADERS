// abb.hpp
// Estrutura de uma Árvore Binária de Busca (ABB) com balanceamento AVL.
//
// The MIT License (MIT)
//
// Copyright (c) 2022 João Vicente Ferreira Lima, UFSM
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>

template<typename T>
struct Abb {
    T dado;         // o dado a ser guardado
    Abb<T>* esq;    
    Abb<T>* dir;
    int altura;        // valor de altura
};

template<typename T>
int abb_altura(Abb<T>* no)
{
    if(no == nullptr)
        return 0;
    return no->altura;
}

template<typename T>
int abb_get_fb(Abb<T>* no)
{
    if(no == nullptr)
        return 0;
    return (abb_altura(no->esq) - abb_altura(no->dir));
}
template<typename T>
Abb<T>* abb_dir_esq_rotate(Abb<T>* x){
    x->dir= abb_dir_rotate(x->dir);
    return abb_esq_rotate(x);
}

template<typename T>
Abb<T>* abb_esq_dir_rotate(Abb<T>* x){
    x->esq= abb_esq_rotate(x->esq);
    return abb_dir_rotate(x);
}

// Faz uma rotação a esquerda do nó x.
// Retorna o novo nó raiz (y).
template<typename T>
Abb<T>* abb_esq_rotate(Abb<T>* x)
{
    Abb<T>* y = x->dir;
    Abb<T>* b= y->esq;
    y->esq= x;
    x->dir= b;

    x->altura = 1 + std::max(
        abb_altura(x->esq),
        abb_altura(x->dir)
    );
    y->altura = 1 + std::max(
        abb_altura(y->esq),
        abb_altura(y->dir)
    );
    return y;
}

// Faz uma rotação a direita do nó x.
// Retorna o novo nó raiz (y).
template<typename T>
Abb<T>* abb_dir_rotate(Abb<T>* x)
{
    Abb<T>* y = x->esq;
    Abb<T>* b= y->dir;

    y->dir= x;
    x->esq= b;

    x->altura = 1 + std::max(
        abb_altura(x->esq),
        abb_altura(x->dir)
    );
    y->altura = 1 + std::max(
        abb_altura(y->esq),
        abb_altura(y->dir)
    );

    return y;
}

// inicia o no da arvore com valores nulos
template<typename T>
Abb<T>* abb_inicia(T v)
{
    Abb<T>* no = new Abb<T>;
    no->dado = v;
    no->altura = 1;
    no->esq = nullptr;
    no->dir = nullptr;

    return no;
}

// Insere um no pre-alocado na arvore
// - primeiro, verifica se a árvore é vazia
// - procura o nó adequado para inserção
// - atualiza a altura do nó recursivamente
// - verifica o balanceamento do nó e executa rotações necessárias
//
// Retorna o nó raiz, ou outro nó caso precisar de rotações.
template<typename T>
Abb<T>* abb_insere( Abb<T>* no, T v )
{
    if( no == nullptr )
        return abb_inicia(v);

    // o novo valor e menor que o meu?
    if(  v < no->dado )
        no->esq = abb_insere( no->esq, v );
    else if( v > no->dado ) // o novo valor e maior ou igual
        no->dir = abb_insere( no->dir, v );
    else 
        return no;
    
    no->altura = 1 + std::max(
        abb_altura(no->esq),
        abb_altura(no->dir)
    );
    //to do
    int FB= abb_get_fb(no);
    if( FB > 1){
        if(v < no->esq->dado){
            return abb_dir_rotate(no);
        }else if(v > no->esq->dado){//esq dir
            return abb_esq_dir_rotate(no); //rotação dupla
        }
    }

    if( FB < -1){
        if(v > no->dir->dado){
            return abb_esq_rotate(no);
        }else if(v < no->dir->dado){ //dir esq
            return abb_dir_esq_rotate(no);
        }
    }

    return no;
}

template<typename T>
Abb<T>* abb_no_minimo( Abb<T>* no )
{
    Abb<T>* curr = no;
    while( curr->esq != nullptr )
        curr = curr->esq;
    return curr;
}

template<typename T>
Abb<T>* abb_acha_valor( Abb<T>* no, T v ){
    if(no->dado != v){
        
        if(  v < no->dado )
            no->esq = abb_remove( no->esq, v );
        else if( v > no->dado ) // o novo valor e maior ou igual
            no->dir = abb_remove( no->dir, v );
        
    }
    return no;
}

/* DEISE if(no->esq == nullptr && no->dir == nullptr){
        delete no;
    }else if(no->esq== nullptr){

        Abb<T>* t= no;
        no= no->dir;
        delete t;
    }else if(no->dir== nullptr){
        Abb<T>* t= no;
        no= no->esq;
        delete t;
    }else{
        Abb<T>* t= no->esq;
        while(t->dir != nullptr) t=t->dir;
        no->dado = t->dado;
        t->dado= v;
        t->esq = abb_remove(t->esq, v); 
    }*/

// Remove o nó de valor "v"
// - procura o nó adequado com o valor
// - se o nó tem uma sub-árvore, troca por ela.
// - senão, troca o nó pelo nó mais a esquerda da sub-árvore a direita
// - atualiza as alturas recursivamente
// - verifica se o nó precisa de balanceamento.
template<typename T>
Abb<T>* abb_remove( Abb<T>* no, T v )
{   
    if(no == nullptr){
        return no;
    }

    /*if( no->dado != v ){*/

    if(  v < no->dado )
        no->esq = abb_remove( no->esq, v );
    else if( v > no->dado ) // o novo valor e maior ou igual
        no->dir = abb_remove( no->dir, v );
    else{
        if(no->esq == nullptr || no->dir == nullptr){
            Abb<T>* temp;
            if(no->esq != nullptr){
                temp= no->esq;
            }else{
                temp= no->dir;
            }
            if(temp == nullptr){
                temp = no;
                no=nullptr;
            }else{
                *no = *temp;
            }
            delete temp;
        }else{
            Abb<T>* y = abb_no_minimo(no->dir);
            no->dado = y->dado;
            y->dado= v;
            no->dir = abb_remove(no->dir, v);
        }
    }

    if(no == nullptr){
        return no;
    }
    //atualiza altura
    no->altura = 1 + std::max(
        abb_altura(no->esq),
        abb_altura(no->dir)
    );

    int FB= abb_get_fb(no);
    if(FB > 1){
        int FBE =abb_get_fb(no->esq);
        if(FBE >= 0){
            return abb_dir_rotate(no);
        }else{
            return abb_esq_dir_rotate(no);
        }
    }
    if(FB< -1){
        int FBD = abb_get_fb(no->dir);
        if(FBD <= 0){
            return abb_esq_rotate(no);
        }else{
            return abb_dir_esq_rotate(no);
        }
    }

    return no;
}

// faz o percurso pre-ordem.
// A visita e imprimir o valor de cada no
template<typename T>
void abb_emOrdem(Abb<T>* a)
{
    // primeiro esquerda
    if( a != nullptr ){
        abb_emOrdem(a->esq);
        std::cout << a->dado << "(" << a->altura << ") ";
        abb_emOrdem(a->dir);
    }
}   

template<typename T>
void abb_preOrdem(Abb<T>* a)
{
    // primeiro esquerda
    if( a != nullptr ){
        std::cout << a->dado << "(" << a->altura << ") ";
        abb_preOrdem(a->esq);
        abb_preOrdem(a->dir);
    }
}   

template<typename T>
void abb_destroi(Abb<T>* a)
{
    if(a != nullptr){
        abb_destroi(a->esq);
        abb_destroi(a->dir);
        delete a;
    }
}
template<typename T>
int no_sem_filhos(Abb<T>* no){

    int FB = abb_get_fb(no);
    int pos;

    if(no->esq == nullptr && no->dir == nullptr){
        return no->dado.c.centro.y+5;
    }

    if(FB > 0){
        pos= no_sem_filhos(no->esq);
    }else{
        pos= no_sem_filhos(no->dir);
    }
    return pos;
}
template<typename T>
void invaders_limpa(Abb<T>* no){
    if(no==nullptr){
        return;
    }
    
    invaders_limpa(no->esq);
    invaders_limpa(no->dir);
    delete no;
}