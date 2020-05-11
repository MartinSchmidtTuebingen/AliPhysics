/*************************************************************************************************
***  Add Fragmentation Function Task ***
**************************************************************************************************
The ID fragmentation function task expects an ESD filter and jet finder running before this task. 
Or it runs on delta-AODs filled with filtered tracks and jets before.

** Parameters **
(char) recJetsBranch: branch in AOD for (reconstructed) jets
(char) genJetsBranch: branch in AOD for (generated) jets
(char) jetType: "AOD"   jets from recJetsBranch
                "AODMC" jets from genJetsBranch
                "KINE"  jets from PYCELL
                 +"b" (e.g. "AODb") jets with acceptance cuts
(char) trackType: "AOD"     reconstructed tracks from AOD filled by ESD filter (choose filter mask!)
                  "AODMC"   MC tracks from AOD filled by kine filter
                  "KINE"    kine particles from MC event 
                  +"2" (e.g. "AOD2")  charged tracks only
                  +"b" (e.g. "AOD2b") with acceptance cuts
(UInt_t) filterMask: select filter bit of ESD filter task

Typical parameters to run on 11a1* (MC_pp@7TeV):
"clustersAOD_ANTIKT", "", "clustersAODMC2_ANTIKT", "AODMCb", "AODMC2b", AliAnalysisManager::GetGlobalInt("kHighPtFilterMask", gDebug), 
-0.4, 0, 1000*AliAnalysisManager::GetGlobalDbl("kTrackPtCut", gDebug), 0, "_Skip00", "", "_Skip00", 0.4, -1, 0, 0, kFALSE,
"PWGJE_taskPID_Jets", "", "PWGJE_taskPID_Jets_Inclusive", "" 

***************************************************************************************************/

void postConfig(AliAnalysisTaskIDFragmentationFunction* task, TString suffixPIDtaskJets1, TString suffixPIDtaskJets2,
                TString suffixPIDtaskInclusive1, TString suffixPIDtaskInclusive2) {

//   task->SetBckgType(AliAnalysisTaskIDFragmentationFunction::kBckgPerp2,
//         AliAnalysisTaskIDFragmentationFunction::kBckgPerp,
//           AliAnalysisTaskIDFragmentationFunction::kBckgPerp2Area,
//             AliAnalysisTaskIDFragmentationFunction::kBckgOutAJStat,
//             AliAnalysisTaskIDFragmentationFunction::kBckgOut2J);

//   task->SetBranchRecBackClusters("");

   // Define histo bins
   //task->SetFFHistoBins(23, 5, 120, 480, 0., 120.,70,  0., 7., 52, 0.,  1.3);
//    task->SetQATrackHistoBins(2400,0,120); // 50 MeV binning for comp to track dN/dpt prel. plot
   
   // JS on
//    task->SetJSMode();
   
//    task->SetEffMode(0);
  
  // Set name of PID framework tasks
   
  // Invalid: Second suffix set, but first one not set -> No PID tasks set
  const Int_t numJetPIDtasks = (suffixPIDtaskJets1 != "") * ((suffixPIDtaskJets1 != "") + (suffixPIDtaskJets2 != ""));
  if (numJetPIDtasks > 0) {
    TString namesJetPIDtasks[numJetPIDtasks];
    namesJetPIDtasks[0] = suffixPIDtaskJets1;
    if (numJetPIDtasks > 1)
      namesJetPIDtasks[1] = suffixPIDtaskJets2;
    task->SetNamesOfJetPIDtasks(numJetPIDtasks, namesJetPIDtasks);
  }
  else
    task->SetNamesOfJetPIDtasks(numJetPIDtasks, 0x0);
  
  // Same for inclusive
  const Int_t numInclusivePIDtasks = (suffixPIDtaskInclusive1 != "") *
                                      ((suffixPIDtaskInclusive1 != "") + (suffixPIDtaskInclusive2 != ""));
  if (numInclusivePIDtasks > 0) {
    TString namesInclusivePIDtasks[numInclusivePIDtasks];
    namesInclusivePIDtasks[0] = suffixPIDtaskInclusive1;
    if (numInclusivePIDtasks > 1)
      namesInclusivePIDtasks[1] = suffixPIDtaskInclusive2;
    task->SetNamesOfInclusivePIDtasks(numInclusivePIDtasks, namesInclusivePIDtasks);
  }
  else
    task->SetNamesOfInclusivePIDtasks(numInclusivePIDtasks, 0x0);
  
  printf("PID framework:\n");
  printf("Jet PID tasks: ");
  for (Int_t i = 0; i < numJetPIDtasks; i++)
    printf("%s ", task->GetNamesOfJetPIDtasks()[i].Data());
  printf("\n");
  printf("Inclusive PID task: ");
  for (Int_t i = 0; i < numInclusivePIDtasks; i++)
    printf("%s ", task->GetNamesOfInclusivePIDtasks()[i].Data());
  printf("\n");
}


AliAnalysisTaskIDFragmentationFunction *AddTaskIDFragmentationFunction(UInt_t iFlag=1, UInt_t filterMask=32, Int_t eventClass=0){
        
        AliAnalysisTaskIDFragmentationFunction *ff=0;

        // UA1 Jets
        // only reconstructed (default)
  if(iFlag&(1<<0)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "", "", "", filterMask, 0.4,0,1000., eventClass);
        // charged MC tracks and jets
  if(iFlag&(1<<1)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "jetsAODMC2_UA1", "AODMC", "AODMC2", filterMask, 0.4,0,1000., eventClass);
        // charged MC tracks and jets with acceptance cuts
  if(iFlag&(1<<2)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "jetsAODMC2_UA1", "AODMCb", "AODMC2b", filterMask, 0.4,0,1000., eventClass);
        // kine tracks in acceptance, pythia jets in acceptance
  if(iFlag&(1<<3)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "", "KINEb", "KINEb", filterMask, 0.4,0,1000., eventClass);
        // reconstructed charged tracks after cuts, MC jets in acceptance 
  if(iFlag&(1<<4)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "jetsMC2b", "AODMCb", "AOD2b", filterMask, 0.4,0,1000., eventClass);
  // reconstruction efficiency: pointing with rec jet axis into gen tracks 
  if(iFlag&(1<<5)) ff = AddTaskIDFragmentationFunction("jetsAOD_UA1", "", "jetsAODMC2_UA1", "AODb", "AODMC2b", filterMask, 0.4,0,1000., eventClass);



      // Jet background subtracted
  // anti-kt, pt cut 1 GeV
  if(iFlag&(1<<20)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.4,2,1000.,eventClass, "_Skip00");
  // anti-kt, pt cut 2 GeV
  if(iFlag&(1<<21)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.4,2,2000.,eventClass, "_Skip00");
  // anti-kt, pt cut 150 MeV
  if(iFlag&(1<<22)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.2,2,150.,eventClass, "_Skip00");

  
  // Jet background subtracted
  if(iFlag&(1<<23)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.4,2,150.,eventClass, "_Skip00");
        // charged MC tracks and jets
  if(iFlag&(1<<24)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "jetsAODMC2_FASTJET", "AODMC", "AODMC2", filterMask, 0.4,2,150.,eventClass, "_Skip00");
        // charged MC tracks and jets with acceptance cuts
  if(iFlag&(1<<25)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "jetsAODMC2_FASTJET", "AODMCb", "AODMC2b", filterMask, 0.4,2,150., eventClass, "_Skip00");

       if(iFlag&(1<<26)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.4,1,150.,eventClass, "_Skip00");

       if(iFlag&(1<<27)) ff = AddTaskIDFragmentationFunction("clustersAOD_ANTIKT", "", "", "", "", filterMask, 0.4,3,150.,eventClass, "_Skip00"); 

      // SISCONE 
      if(iFlag&(1<<28)) ff = AddTaskIDFragmentationFunction("jetsAOD_SISCONE", "", "", "", "", filterMask, 0.4,1,150.,eventClass);
      if(iFlag&(1<<29)) ff = AddTaskIDFragmentationFunction("jetsAOD_SISCONE", "", "", "", "", filterMask, 0.4,2,150.,eventClass);
      if(iFlag&(1<<30)) ff = AddTaskIDFragmentationFunction("jetsAOD_SISCONE", "", "", "", "", filterMask, 0.4,3,150.,eventClass);

  return ff;
}

// _______________________________________________________________________________________

AliAnalysisTaskIDFragmentationFunction *AddTaskIDFragmentationFunctionAllCent(
        const char* recJetsBranch,
  const char* recJetsBackBranch,
  const char* genJetsBranch,
  const char* jetType,
  const char* trackType,
  UInt_t filterMask,
        Float_t radius,
        int kBackgroundMode,
        Int_t PtTrackMin,
        TString BrOpt="",
        TString BrOpt2="",
        TString BrOpt3="",
        Float_t radiusBckg=0.4,
  Int_t   FFMaxTrackPt = -1,
  Float_t FFMinNTracks = 0,
  TString suffixPIDtaskJets1 = "",
  TString suffixPIDtaskJets2 = "",
  TString suffixPIDtaskInclusive1 = "",
  TString suffixPIDtaskInclusive2 = "")
{

  // adds task with  given configuration for all centralities
  
  AliAnalysisTaskIDFragmentationFunction *ff=0;

  for(Int_t eventClass=1; eventClass<=4; eventClass++){
    
    ff = AddTaskIDFragmentationFunction(recJetsBranch,
              recJetsBackBranch,
              genJetsBranch,
              jetType,
              trackType,
              filterMask,
              radius,
              kBackgroundMode,
              PtTrackMin,
              eventClass,
              BrOpt,
              BrOpt2,
              BrOpt3,
              radiusBckg
              FFMaxTrackPt,
              FFMinNTracks,
              suffixPIDtaskJets1,
              suffixPIDtaskJets2,
              suffixPIDtaskInclusive1,
              suffixPIDtaskInclusive2);
  }
  
  return ff;
}

// _______________________________________________________________________________________

AliAnalysisTaskIDFragmentationFunction *AddTaskIDFragmentationFunction(
  const char* recJetsBranch,
  const char* recJetsBackBranch,
  const char* genJetsBranch,
  const char* jetType,
  const char* trackType,
  UInt_t filterMask,
  Float_t radius,
  Int_t kBackgroundMode,
  Int_t PtTrackMin,
  Int_t eventClass=0,
  TString BrOpt="",
  TString BrOpt2="",
  TString BrOpt3="",
  Float_t radiusBckg=0.4,
  Int_t FFMaxTrackPt = -1,
  Int_t FFMinNTracks = 0,
  UInt_t filterMaskTracks = 0,
  Bool_t onlyConsiderLeadingJets = kFALSE,
  TString suffixPIDtaskJets1 = "",
  TString suffixPIDtaskJets2 = "",
  TString suffixPIDtaskInclusive1 = "",
  TString suffixPIDtaskInclusive2 = "",
  Float_t MC_pThard_cut = -1.)
{
   // Creates a fragmentation function task,
   // configures it and adds it to the analysis manager.

   //******************************************************************************
   //*** Configuration Parameter **************************************************
   //******************************************************************************

   // space for configuration parameter: histo bin, cuts, ...
   // so far only default parameter used

   Int_t debug = -1; // debug level, -1: not set here

   //******************************************************************************


   
   // Get the pointer to the existing analysis manager via the static access method.
   //==============================================================================
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (!mgr) {
    ::Error("AddTaskIDFragmentationFunction", "No analysis manager to connect to.");
    return NULL;
   }
   
   // Check the analysis type using the event handlers connected to the analysis manager.
   //==============================================================================
   if (!mgr->GetInputEventHandler()) {
   ::Error("AddTaskIDFragmentationFunction", "This task requires an input event handler");
    return NULL;
   }

   TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
   Printf("Data Type: %s", type.Data());

   TString branchRecBackJets(recJetsBackBranch);
   TString branchRecJets(recJetsBranch);
   TString branchGenJets(genJetsBranch);
   TString typeJets(jetType);
   TString typeTracks(trackType);

   if(branchRecBackJets.Length()==0) branchRecBackJets = "noRecBackJets";
   if(branchRecJets.Length()==0) branchRecJets = "noRecJets";
   if(branchGenJets.Length()==0) branchGenJets = "noGenJets";
   if(typeTracks.Length()==0) typeTracks = "trackTypeUndef";
   if(typeJets.Length()==0)   typeJets   = "jetTypeUndef";
   
   // Create the task and configure it.
   //===========================================================================

   AliAnalysisTaskIDFragmentationFunction *task = new AliAnalysisTaskIDFragmentationFunction(
        Form("Fragmentation_Function_%s_%s_%s_%s_filterMaskTracks%d", branchRecJets.Data(), branchGenJets.Data(), typeJets.Data(),
             typeTracks.Data(), filterMaskTracks));
   
   if(debug>=0) task->SetDebugLevel(debug);

   task->SetEventSelectionMask(AliVEvent::kMB | AliVEvent::kINT8 | AliVEvent::kINT7);
   task->SetEventClass(eventClass);
  
   // Set default parameters 
   // Cut selection 
   task->SetFFRadius(radius); 
//    task->SetFFBckgRadius();     // default: R = 0.7
//    task->SetQAMode();           // default: qaMode = 3
//    task->SetFFMode();           // default: ffMode = 1
//    task->SetIDFFMode(0);        // default: IDffMode = 0
//    task->SetEffMode(0);         // default: effMode = 1
//    task->SetHighPtThreshold();  // default: pt > 5 Gev
// 
//    task->SetBckgMode(1);        // default: bgMode = 1 
//    task->SetBckgType();
//    task->SetBranchRecBackClusters(Form("clustersAOD_KT04_B0_Filter%05d_Cut00150_Skip00",filterMask));
   
   task->SetOnlyLeadingJets(onlyConsiderLeadingJets); // default: kFALSE
   
   task->SetMCPtHardCut(MC_pThard_cut);
   
   // Define histo bins
//    task->SetFFHistoBins(23, 5, 120, 480, 0., 120.,70,  0., 7.,22,  0.,  1.1);
//  
//    task->SetQAJetHistoBins();
//    task->SetQATrackHistoBins();

//    if(FFMaxTrackPt>0) task->SetFFMaxTrackPt(FFMaxTrackPt);
//    if(FFMinNTracks>0) task->SetFFMinNTracks(FFMinNTracks);

   mgr->AddTask(task);

   // Create ONLY the output containers for the data produced by the task.
   // Get and connect other common input/output containers via the manager as below
   //==============================================================================

   TString strList(Form("idfracfunc_%s_%s_%s_%s_cl%d", branchRecJets.Data(), branchGenJets.Data(), typeTracks.Data(), typeJets.Data(), eventClass));
   
   TString strDir(Form("%s:PWGJE_IDFragmentationFunction_%s_%s_%s_%s_cl%d", 
           AliAnalysisManager::GetCommonFileName(), branchRecJets.Data(), branchGenJets. Data(), 
           typeTracks.Data(), typeJets.Data(), eventClass));


   if(FFMaxTrackPt>0){
     strList += Form("_FFMaxPt%d", FFMaxTrackPt);
     strDir  += Form("_FFMaxPt%d", FFMaxTrackPt);
   }
   if(FFMinNTracks>0){
     strList += Form("_minNTr%d",FFMinNTracks);
     strDir  += Form("_minNTr%d",FFMinNTracks);
   }

   if(radius<0){
     strList += "_trackRefs";
     strDir  += "_trackRefs";
   }
   if(filterMaskTracks){
     strList += Form("_TrackFilter%05d",filterMaskTracks);
     strDir  += Form("_TrackFilter%05d",filterMaskTracks);
   }
   
   AliAnalysisDataContainer *coutput_FragFunc = mgr->CreateContainer(strList,TList::Class(),
                     AliAnalysisManager::kOutputContainer,
                     strDir);   
   
   mgr->ConnectInput  (task, 0, mgr->GetCommonInputContainer());
   //mgr->ConnectOutput (task, 0, mgr->GetCommonOutputContainer());// Comment to run locally
   mgr->ConnectOutput (task, 1, coutput_FragFunc);   
   
   postConfig(task, suffixPIDtaskJets1, suffixPIDtaskJets2, suffixPIDtaskInclusive1, suffixPIDtaskInclusive2);
   
   return task;
}

