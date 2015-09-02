#ifndef JUDY_BIT_MAP_H
#define JUDY_BIT_MAP_H
#include "Judy.h"
#include "GBase.h"

class JBitMap {
 protected:
  Pvoid_t judy;
 public:
   bool set(const Word_t idx, bool v) {
     int r;
     if (v) {
       J1S(r, judy, idx);
       }
     else {
       J1U(r, judy, idx);
       }
     return (bool)r;  
  }
  bool get(const Word_t idx) const {
    int r;
    J1T(r, judy, idx);
    return (bool)r;
  }
  
  class JBitNode {
    friend class JBitMap;
   protected:
    JBitMap* bitmap;
    Word_t  jidx;
    JBitNode():bitmap(NULL), jidx(0) { }
    void nullcheck() {
      if (bitmap==NULL)
    	  GError("Error: operator= called for NULL JBitMap!\n");
    }
   public:
    JBitNode(JBitMap* b, Word_t ri):bitmap(b), jidx(ri) { }
    ~JBitNode() { }
    JBitNode& operator=(bool v) {
      nullcheck();
      bitmap->set(jidx, v);
      return *this;
    }
    JBitNode& operator=(JBitNode& t) {
       if (this!=&t) {
         bitmap->set(jidx, t.bitmap->get(jidx));
       }
       nullcheck();
       return *this;
    }
    
    operator bool() {
     nullcheck();
     return bitmap->get(jidx);
    }
    
  }; //class JBitNode
 
  JBitMap() {
     judy = (Pvoid_t)NULL; 
  }
  ~JBitMap() {
    Word_t freed;
    J1FA(freed, judy);
  }

  JBitNode operator[](Word_t idx) {
    return JBitNode(this, idx);
  }
  
  bool operator[](Word_t idx) const {
    return this->get(idx); 
  }

  //returns the number of bits which are set (population count)
  uint count() { 
    Word_t r;
    J1C(r, judy, 0, -1);
    return (uint)r;
  }
  //range count: return number of bits set between indexes idx1 and idx2 (inclusive)
  uint count(Word_t idx1, Word_t idx2=-1) {
    Word_t r;
    J1C(r, judy, idx1, idx2);
    return (uint)r;
  }

  //return the index of the Nth set bit in the bit array, or -1 if no such bit exists
  long getNth(Word_t Nth) {
     int r;
     Word_t idx;
     J1BC(r, judy, Nth, idx);
     return ( r? idx : -1 );
  }
  //return the index of the first bit set, at or after index Idx; -1 if not found
  long getFirst(Word_t idx=0) {
     int r;
     J1F(r, judy, idx);
     return (r? idx : -1);
  }
  //return the index of the first bit set AFTER Idx (-1 if not found)
  long getNext(Word_t idx) {
     int r;
     J1N(r, judy, idx);
     return (r? idx : -1);
  }
  //return the index of the last bit set at or BEFORE idx (-1 if not found);
  long getLast(Word_t idx = -1) {
     int r;
     J1L(r, judy, idx);
     return (r ? idx : -1);
  }
  //return the index of the last bit set BEFORE idx (-1 if not found);
  long getPrev(Word_t idx) {
     int r;
     J1P(r, judy, idx);
     return (r? idx : -1);
  }
  //--- now the same for unset bits (i.e. absent indexes): 
  //return the index of the first clear bit, at or after index Idx; -1 if not found
  long getFirst0(Word_t idx=0) {
     int r;
     J1FE(r, judy, idx);
     return (r? idx : -1);
  }
  //return the index of the first clear bit AFTER Idx (-1 if not found)
  long getNext0(Word_t idx) {
     int r;
     J1NE(r, judy, idx);
     return (r? idx : -1);
  }
  //return the index of the last clear bit at or BEFORE idx (-1 if not found);
  long getLast0(Word_t idx = -1) {
     int r;
     J1LE(r, judy, idx);
     return (r ? idx : -1);
  }
  //return the index of the last clear bit BEFORE idx (-1 if not found);
  long getPrev0(Word_t idx) {
     int r;
     J1PE(r, judy, idx);
     return (r ? idx : -1);
  }
};

#endif
