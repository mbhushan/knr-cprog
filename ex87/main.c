/*
    Exercise 8-7. malloc accepts a size request without checking its plausibility; free believes that the
    it is asked to free contains a valid size field. Improve these routines so they take more pains with error checking.
*/
#include <stdio.h>
#include <limits.h>

#define NALLOC 1024 //min number ofheader units to request in malloc/calloc.
typedef long Align; // for alignment to long memory.

union header {
    struct {
        union header *ptr;
        unsigned size; // size of this block, in header units.
    }s;
    Align x;
};

typedef union header Header;
static Header base; // empty list of free memory to get started, starts out as the left most end of the list.
static Header *freep = NULL; // start of the free list.

void *mycalloc(unsigned n, size_t size);
void *mymalloc(unsigned nbytes);
static Header *morecore(unsigned nunits);
void myfree(void *ap);
char *sbrk(int); //syscall for more memory, apprently you dont need to include headers, just define the function and call it.


int main() {
    char *b = mymalloc(10);
    myfree(b);
    myfree(&base);
    myfree(freep);
    return 0;
}

// gets n times size number of bytes of memory from mymalloc and init with zero.
void *mycalloc(unsigned n, size_t size) {
    char *p;
    if ((p = mymalloc(n*size)) == NULL) return NULL;
    for (unsigned i=0; i<n*size; i++) {
        p[i] = '\0'; // go through each byte and set to zero.
    }
    return p;
}

void *mymalloc(unsigned nbytes) {
    Header *p, *prevp;
    if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header)) {
        printf("Error: invalid nbytes size request\n", nbytes);
        return NULL;
    }

    unsigned nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p=prevp->s.ptr; ; prevp=p, p=p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) {
            if ((p = morecore(nunits)) == NULL) return NULL;
        }
    }
}

// ask system for more memory, units must be large enough for mem request and header
static Header *morecore(unsigned nunits) {
   char *cp; //used to point to free mem returned from sbrk call.
   Header *up;
   if (nunits < NALLOC) nunits = NALLOC;

    cp = sbrk(nunits * sizeof(Header));
    if (cp == (char *)-1) return NULL;

    up = (Header *)cp;
    up->s.size = nunits;
    myfree((void *)(up+1));
    return freep;
}

void myfree(void *ap) {
    Header *bp, *p;
    if (ap == NULL) {
        printf("Error: null pointer passed to myfree\n");
        return;
    }

    bp = (Header *)ap - 1;
    if (bp->s.size == 0) {
        printf("Error: cant free ap with 0 units\n");
        return;
    }

    for (p=freep; !(bp > p && bp < p->s.ptr); p=p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
    }

    if (bp+bp->s.size == p->s.ptr && bp->s.size < UINT_MAX - p->s.ptr->s.size) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p+p->s.size == bp && p->s.size < UINT_MAX - bp->s.size) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}
