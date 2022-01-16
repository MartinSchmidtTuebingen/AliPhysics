#ifndef ALIFEMTOCORRFCTNPDTHE3_H
#define ALIFEMTOCORRFCTNPDTHE3_H

#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TNtuple.h"
#include "TString.h"

#include "AliFemtoCorrFctn.h"

#include "AliAODInputHandler.h"
#include "AliAnalysisManager.h"

/// \class AliFemtoCorrFctnpdtHe3
/// \brief KStar correlation function for p-d/t/He3 
///         Based on AliFemtoCorrFctnKStar.cxx!
/// \authors  Dong-Fang Wang, Fudan University, China, <dongfang.wang@cern.ch>
///

class AliFemtoCorrFctnpdtHe3 : public AliFemtoCorrFctn {
    public:
        AliFemtoCorrFctnpdtHe3();
        AliFemtoCorrFctnpdtHe3(const char* title,
                        const int nbins,
                        const float KStarLo,
                        const float KStarHi);
        AliFemtoCorrFctnpdtHe3(const AliFemtoCorrFctnpdtHe3 & aCorrFctn);
        virtual ~AliFemtoCorrFctnpdtHe3();
        AliFemtoCorrFctnpdtHe3& operator=(const AliFemtoCorrFctnpdtHe3& aCorrFctn);
        
        virtual AliFemtoString Report();
        virtual TList* GetOutputList();
        virtual void Finish();
        void Write();

        virtual void AddRealPair(AliFemtoPair* aPair);
        virtual void AddMixedPair(AliFemtoPair* aPair);
        void SetIsHe3Pair(int isOrNot);
        AliFemtoPair * ChangeP2Mom(AliFemtoPair* aPair);
        int ReVelocityGate(AliFemtoPair* aPair);
        void SetP1AndP2Mass(float p1Mass,float p2Mass);
        virtual AliFemtoCorrFctnpdtHe3* Clone() const  { return new AliFemtoCorrFctnpdtHe3(*this); }
    protected:
        int isHe3Pair;
        TString fTitle;
        int fNbinsKStar;
        double fKStarLow, fKStarHigh;
        float fP1Mass, fP2Mass;
        TH1D* fNumerator;          // numerator - real pairs
        TH1D* fDenominator;        // denominator - mixed pairs

        // velocity gate 11.23
        TH1D *fP1EarlierP2Num;
        TH1D *fP1EarlierP2Dum;
        TH1D *fP2EarlierP1Num;
        TH1D *fP2EarlierP1Dum;
 
        TH3F *fNumHigh3F;
        TH3F *fDenHigh3F;

      
};
#endif


