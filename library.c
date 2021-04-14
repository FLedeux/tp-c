#include "library.h"
#include <stdlib.h>
#include <string.h>

library* library_init(int initial_capacity){
    
    library* l = calloc(1,sizeof(library));
    l->liste_entry= calloc(initial_capacity,sizeof(entry*));
    l->capacityCurrent=0;
    l->capacityMax = initial_capacity;

    return l;
}
void library_destroy(library* self){
    for(int i=0;i<self->capacityCurrent;i++){
        free(self->liste_entry[i]);
    }
    free(self->liste_entry);
    free(self);
}
int library_books_count(library *self){
    return self->capacityCurrent;
}



int get_index_book(library* self, int some_book_id){
    int i=0;
    while(i<self->capacityCurrent){
        if(self->liste_entry[i]->livre->identifiant==some_book_id){
            return i;
        }
        i++;
    }
    return -1;
}

void library_register_book(library* self, book* some_book){
    int index = get_index_book(self,some_book->identifiant);
    if(index>=0){
        self->liste_entry[index]->nb++;
        
    }
    else if(self->capacityCurrent<self->capacityMax){
        self->liste_entry[self->capacityCurrent] = calloc(1,sizeof(entry));
        self->liste_entry[self->capacityCurrent]->nb = 1;
        self->liste_entry[self->capacityCurrent]->livre = some_book;
        self->capacityCurrent++;
    }
}


book* library_find_by_id(library *self, int id){
    int index = get_index_book(self, id);
    if(index==-1){
        return NULL;
    }
    return self->liste_entry[index]->livre;
}


book* library_find_by_title(library *self,char* title){
    int i=0;
    int nb =0;
    while(i<self->capacityCurrent){
        if(strcmp(self->liste_entry[i]->livre->title,title)==0){
            return self->liste_entry[i]->livre;
        }
        i++;
    }
    return NULL;
    
}
int library_is_book_available(library* self,char* title){
    int i=0;
    int nb =0;
    while(i<self->capacityCurrent){
        
        if(strcmp(self->liste_entry[i]->livre->title,title)==0){
            nb = self->liste_entry[i]->nb;
            break;
        }
        i++;
    }
    return nb;
}



book* library_borrow_book(library* self, char* title){
    book* b = library_find_by_title(self,title);
    if(b == NULL){
        return NULL;
    }
    
    int i = get_index_book(self, b->identifiant);
    if(self->liste_entry[i]->nb>0){
        self->liste_entry[i]->nb--;
        return b;
    }
    
    return NULL;
}
int library_return_book(library * self,book* some_book){
    int i = get_index_book(self,some_book->identifiant);
    if(i<0){
        return 0;
    }

    self->liste_entry[i]->nb++;
    return self->liste_entry[i]->nb;
}


book** library_find_by_author(library* self, char* author){
    int size =0;
    book** tab_b=NULL;
    for(int i=0;i<self->capacityCurrent;i++){
        if(strcmp(self->liste_entry[i]->livre->auteur,author)==0){
            size++;
            tab_b = reallocarray(tab_b,size, sizeof(book*));
            tab_b[size-1]= self->liste_entry[i]->livre;
        }
    }
    return tab_b;
}