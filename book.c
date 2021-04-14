#include "book.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int id_count=0;

book* book_init(char* title,char* author){
    book* b = calloc(1,sizeof(book));
    b->title = strdup(title);
    b->auteur = strdup(author);
    b->identifiant = id_count;
    id_count++;

    return b;
}
void book_destroy(book* self){
    free(self->title);
    free(self->auteur);
    free(self);
}
int book_get_id(book* self){
    return self->identifiant;
}
char* book_get_title(book* self){
    return self->title;
}
char* book_get_author(book * self){
    return self->auteur;
}