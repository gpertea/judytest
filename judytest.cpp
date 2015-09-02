#include "GBase.h"
#include "GArgs.h"
#include "GStr.h"
//#include "GBitVec.h"
//#include "GList.hh"
//#include "GHash.hh"
#include "JBitMap.h"

#define USAGE "Usage:\n\
judytest [-h][-t] [-o <file.out>]\n\
 "

void bitError(int idx) {
 GError("Error bit checking (index %d)!\n", idx);
}


int main(int argc, char * const argv[]) {
 //GArgs args(argc, argv, "hg:c:s:t:o:p:help;genomic-fasta=COV=PID=seq=out=disable-flag;test=");
 GArgs args(argc, argv, "hto:");
 //fprintf(stderr, "Command line was:\n");
 //args.printCmdLine(stderr);
 //args.printError(USAGE, true);
 //if (args.getOpt('h') || args.getOpt("help"))
 
 if (args.getOpt('h'))
     {
     GMessage("%s\n", USAGE);
     exit(1);
     }

 // testing GBitVec/JBitMap
    JBitMap bits;
    GMessage(">>> -- Start JBitMap Test -- \n");
    if (bits[1092]) bitError(1092);
    bits[1092]=1;
    //bits.resize(2049);
    if (bits[2048]) bitError(2048);
    bits[2048]=true;
    if (!bits[2048]) bitError(2048);
    //bits.resize(4097);
    if (!bits[2048]) bitError(2048);
    if (bits[4096]) bitError(4096);
    bits[4096]=true;
    if (!bits[4096]) bitError(4096);
    /*GBitVec bits2(64);
    Gswap(bits, bits2);
    if (!bits2[2048]) bitError(2048);
    if (!bits2[4096]) bitError(4096);
    */
    GMessage("<<< -- End JBitMap Test (count: %d, min index %d, max index %d) --\n", 
           (int)bits.count(), (int)bits.getFirst(), (int)bits.getLast());
 //-----------
 return 0;
}

