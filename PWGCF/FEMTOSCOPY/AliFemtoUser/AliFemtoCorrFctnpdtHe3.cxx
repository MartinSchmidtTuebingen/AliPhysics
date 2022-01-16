///
/// \file AliFemtoCorrFctnpdtHe3.cxx
///

#include "AliFemtoCorrFctnpdtHe3.h"
const float ProtonMass = 0.9383;
const float DeuteronMass= 2.225;
const float TritonMass = 2.8089;
const float He3Mass = 2.8084;
/*
AliFemtoCorrFctnpdtHe3::AliFemtoCorrFctnpdtHe3():
    AliFemtoCorrFctnpdtHe3("CorrFctnKStar", 200, 0, 1)
{
// no-op
}
*/
AliFemtoCorrFctnpdtHe3::AliFemtoCorrFctnpdtHe3(const char* title,
                                             const int nbins,
                                             const float KStarLo,
                                             const float KStarHi):
    AliFemtoCorrFctn(),
    isHe3Pair(0),
    fTitle(title),
    fNbinsKStar(nbins),
    fKStarLow(KStarLo),
    fKStarHigh(KStarHi),
    fP1Mass(0.1),
    fP2Mass(0.1),
    fNumerator(nullptr),
    fDenominator(nullptr),
    fP1EarlierP2Num(nullptr),
    fP1EarlierP2Dum(nullptr),
    fP2EarlierP1Num(nullptr),
    fP2EarlierP1Dum(nullptr),
    fNumHigh3F(nullptr),
    fDenHigh3F(nullptr)
{
    
    fNumerator      = new TH1D(TString::Format("Num%s", fTitle.Data()), "fNumerator", nbins, KStarLo, KStarHi);
    fDenominator    = new TH1D(TString::Format("Dum%s", fTitle.Data()), "fDenominator", nbins, KStarLo, KStarHi);
    
    fNumerator->Sumw2();
    fDenominator->Sumw2();

    fP1EarlierP2Num = new TH1D(TString::Format("p1Ep2Num_%s", fTitle.Data()), " ", nbins, KStarLo, KStarHi);
    fP1EarlierP2Dum = new TH1D(TString::Format("p1Ep2Dum_%s", fTitle.Data()), " ", nbins, KStarLo, KStarHi);;
    fP2EarlierP1Num = new TH1D(TString::Format("p2Ep1Num_%s", fTitle.Data()), " ", nbins, KStarLo, KStarHi);;
    fP2EarlierP1Dum = new TH1D(TString::Format("p2Ep1Dum_%s", fTitle.Data()), " ", nbins, KStarLo, KStarHi);;

    fP1EarlierP2Num->Sumw2();
    fP1EarlierP2Dum->Sumw2();
    fP2EarlierP1Num->Sumw2();
    fP2EarlierP1Dum->Sumw2();

    int xybin = 19;
    float testxy[20];
    for(int i=0;i<20;i++){
        testxy[i] = 0.2*float(i+1);
    }
    float testz[101];
    for(int i=0;i<101;i++){
        testz[i] = 0.01*float(i);
    }
    fNumHigh3F = new TH3F(TString::Format("fNumHigh3F_%s", fTitle.Data())," ",xybin,testxy,xybin,testxy,100,testz);
    fDenHigh3F = new TH3F(TString::Format("fDenHigh3F_%s", fTitle.Data())," ",xybin,testxy,xybin,testxy,100,testz);
    fNumHigh3F->Sumw2();
    fDenHigh3F->Sumw2();
}
AliFemtoCorrFctnpdtHe3::AliFemtoCorrFctnpdtHe3(const AliFemtoCorrFctnpdtHe3& aCorrFctn):
    AliFemtoCorrFctn(aCorrFctn),
    isHe3Pair(aCorrFctn.isHe3Pair),
    fTitle(aCorrFctn.fTitle),
    fNbinsKStar(aCorrFctn.fNbinsKStar),
    fKStarLow(aCorrFctn.fKStarLow),
    fKStarHigh(aCorrFctn.fKStarHigh),    
    fP1Mass(aCorrFctn.fP1Mass),
    fP2Mass(aCorrFctn.fP2Mass),
    fNumerator(aCorrFctn.fNumerator ? new TH1D(*aCorrFctn.fNumerator) : nullptr),
    fDenominator(aCorrFctn.fDenominator ? new TH1D(*aCorrFctn.fDenominator) : nullptr),
    fP1EarlierP2Num(aCorrFctn.fP1EarlierP2Num),
    fP1EarlierP2Dum(aCorrFctn.fP1EarlierP2Dum),
    fP2EarlierP1Num(aCorrFctn.fP2EarlierP1Num),
    fP2EarlierP1Dum(aCorrFctn.fP2EarlierP1Dum),
    fNumHigh3F(aCorrFctn.fNumHigh3F),
    fDenHigh3F(aCorrFctn.fDenHigh3F)
{
    


}
AliFemtoCorrFctnpdtHe3::~AliFemtoCorrFctnpdtHe3()
{
    // destructor
    delete fNumerator;
    delete fDenominator;
    
    delete fP1EarlierP2Num;
    delete fP1EarlierP2Dum;
    delete fP2EarlierP1Num;
    delete fP2EarlierP1Dum;
    
    delete fNumHigh3F;
    delete fDenHigh3F;

}
AliFemtoCorrFctnpdtHe3& AliFemtoCorrFctnpdtHe3::operator=(const AliFemtoCorrFctnpdtHe3& aCorrFctn)
{
    // assignment operator
    if (this == &aCorrFctn) {
        return *this;
    }

    AliFemtoCorrFctnpdtHe3::operator=(aCorrFctn);
    isHe3Pair = aCorrFctn.isHe3Pair;
    fTitle = aCorrFctn.fTitle;
    fNbinsKStar = aCorrFctn.fNbinsKStar;
    fKStarLow = aCorrFctn.fKStarLow;
    fKStarHigh = aCorrFctn.fKStarHigh;
    fP1Mass = aCorrFctn.fP1Mass;
    fP2Mass = aCorrFctn.fP2Mass;

    if(fNumerator) delete fNumerator;
        fNumerator = new TH1D(*aCorrFctn.fNumerator);
    if(fDenominator) delete fDenominator;
        fDenominator = new TH1D(*aCorrFctn.fDenominator);


    if(fP1EarlierP2Num) delete fP1EarlierP2Num;
        fP1EarlierP2Num = new TH1D(*aCorrFctn.fP1EarlierP2Num);
    if(fP1EarlierP2Dum) delete fP1EarlierP2Dum;
        fP1EarlierP2Dum = new TH1D(*aCorrFctn.fP1EarlierP2Dum);
    if(fP2EarlierP1Num) delete fP2EarlierP1Num;
        fP2EarlierP1Num = new TH1D(*aCorrFctn.fP2EarlierP1Num);
    if(fP2EarlierP1Dum) delete fP2EarlierP1Dum;
        fP2EarlierP1Dum = new TH1D(*aCorrFctn.fP2EarlierP1Dum);

    fNumHigh3F = new TH3F(*aCorrFctn.fNumHigh3F);
    fDenHigh3F = new TH3F(*aCorrFctn.fDenHigh3F);
    return *this;

}

AliFemtoString AliFemtoCorrFctnpdtHe3::Report()
{
    TString report = "AliFemtoCorrFctnKStar:\n";
    report += TString::Format("Number of entries in numerator:\t%E\n", fNumerator->GetEntries());
    report += TString::Format("Number of entries in denominator:\t%E\n", fDenominator->GetEntries());
    return AliFemtoString((const char *)report);

}
TList* AliFemtoCorrFctnpdtHe3::GetOutputList()
{
    // Prepare the list of objects to be written to the output
    TList *tOutputList = new TList();

    tOutputList->Add(fNumerator);
    tOutputList->Add(fDenominator);

    tOutputList->Add(fP1EarlierP2Num);
    tOutputList->Add(fP1EarlierP2Dum);
    tOutputList->Add(fP2EarlierP1Num);
    tOutputList->Add(fP2EarlierP1Dum);
    
    tOutputList->Add(fNumHigh3F);
    tOutputList->Add(fDenHigh3F);
    return tOutputList;
}
void AliFemtoCorrFctnpdtHe3::Finish()
{
    //cout<<"AliFemtoCorrFctnpdtHe3::Finish()"<<endl;
}
void AliFemtoCorrFctnpdtHe3::Write()
{
    // Write out neccessary objects
    fNumerator->Write();
    fDenominator->Write();

    fP1EarlierP2Num->Write();
    fP1EarlierP2Dum->Write();
    fP2EarlierP1Num->Write();
    fP2EarlierP1Dum->Write();

    fNumHigh3F->Write();
    fDenHigh3F->Write();

}
void AliFemtoCorrFctnpdtHe3::AddRealPair(AliFemtoPair* aPair)
{
    // change momentum of p2!
    AliFemtoPair* fPair = new AliFemtoPair;

    if(isHe3Pair){
        fPair = ChangeP2Mom(aPair);
    }
    else{
        fPair = aPair;
    }

    
    // add true pair
    if (fPairCut && !fPairCut->Pass(fPair)) {
        return;
    }

    double tKStar = fabs(fPair->KStar());
    fNumerator->Fill(tKStar);
    fNumHigh3F->Fill(fPair->Track1()->Track()->Pt(),fPair->Track2()->Track()->Pt(),tKStar); 

    int VelLabel = ReVelocityGate(fPair);
    if(VelLabel == 1){
        fP1EarlierP2Num->Fill(tKStar);
    }
    else if(VelLabel == 2){
        fP2EarlierP1Num->Fill(tKStar);
    }
    else if(VelLabel == 3){
        return;
    }
    
 
}

void AliFemtoCorrFctnpdtHe3::AddMixedPair(AliFemtoPair* aPair)
{
    // change momentum of p2!
    AliFemtoPair* fPair = new AliFemtoPair;

    if(isHe3Pair){
        fPair = ChangeP2Mom(aPair);
    }
    else{
        fPair = aPair;
    }

    // add true pair
    if (fPairCut && !fPairCut->Pass(fPair)) {
        return;
    } 

    double tKStar = fabs(fPair->KStar());
    fDenominator->Fill(tKStar);
    fDenHigh3F->Fill(fPair->Track1()->Track()->Pt(),fPair->Track2()->Track()->Pt(),tKStar);

    int VelLabel = ReVelocityGate(fPair);
    if(VelLabel == 1){
        fP1EarlierP2Dum->Fill(tKStar);
    }
    else if(VelLabel == 2){
        fP2EarlierP1Dum->Fill(tKStar);
    }
    else if(VelLabel == 3){
        return;
    }
    

}
void AliFemtoCorrFctnpdtHe3::SetIsHe3Pair(int isOrNot)
{
    // 0 is not He3 pair, 1 is 
    isHe3Pair = isOrNot;
}
AliFemtoPair * AliFemtoCorrFctnpdtHe3::ChangeP2Mom(AliFemtoPair* aPair)
{
    AliFemtoPair* fPair = new AliFemtoPair;

    AliFemtoParticle *tPart1 = new AliFemtoParticle(*aPair->Track1());
    fPair->SetTrack1(tPart1);

    // modify momentum!
    AliFemtoParticle *tPart2 = new AliFemtoParticle(*aPair->Track2());
    AliFemtoLorentzVector tFourMom2 = AliFemtoLorentzVector(tPart2->FourMomentum());
    tFourMom2.SetPx(2.*tFourMom2.px());
    tFourMom2.SetPy(2.*tFourMom2.py());
    tFourMom2.SetPz(2.*tFourMom2.pz());

    float TotalP = tFourMom2.px() * tFourMom2.px() + tFourMom2.py() * tFourMom2.py() + tFourMom2.pz() * tFourMom2.pz();
    float TotalE = TMath::Sqrt( He3Mass * He3Mass + TotalP);
    tFourMom2.SetE(TotalE);
    tPart2->ResetFourMomentum(tFourMom2);

    fPair->SetTrack2(tPart2);

    return fPair;
}
int AliFemtoCorrFctnpdtHe3::ReVelocityGate(AliFemtoPair* aPair){
    //\ 1: p1 faster than p2
    //\ 2: p2 faster than p1
    //\ 3: bad
    AliFemtoParticle *tPart1 = new AliFemtoParticle(*aPair->Track1());
    AliFemtoLorentzVector tFourMom1 = AliFemtoLorentzVector(tPart1->FourMomentum());
    float TotalP = tFourMom1.px() * tFourMom1.px() + tFourMom1.py() * tFourMom1.py() + tFourMom1.pz() * tFourMom1.pz();
    float TotalE = TMath::Sqrt( fP1Mass * fP1Mass + TotalP);
    float P1velocity = TotalP/TotalE;

    //
    
    AliFemtoParticle *tPart2 = new AliFemtoParticle(*aPair->Track2());
    AliFemtoLorentzVector tFourMom2 = AliFemtoLorentzVector(tPart2->FourMomentum());
    TotalP = tFourMom2.px() * tFourMom2.px() + tFourMom2.py() * tFourMom2.py() + tFourMom2.pz() * tFourMom2.pz();
    TotalE = TMath::Sqrt( fP2Mass * fP2Mass + TotalP);
    float P2velocity = TotalP/TotalE;

    int ReLabel = 3;
    if(P1velocity > P2velocity){
        ReLabel = 1;
    }
    if(P1velocity < P2velocity){
        ReLabel = 2;
    }

    return ReLabel;
}
void AliFemtoCorrFctnpdtHe3::SetP1AndP2Mass(float p1Mass,float p2Mass){

    fP1Mass = p1Mass;
    fP2Mass = p2Mass;
}


