// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__RooUnfold
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "RooFitUnfold.h"
#include "RooUnfold.h"
#include "RooUnfold/TUnfold/TUnfold.h"
#include "RooUnfold/TUnfold/TUnfoldBinning.h"
#include "RooUnfold/TUnfold/TUnfoldBinningXML.h"
#include "RooUnfold/TUnfold/TUnfoldDensity.h"
#include "RooUnfold/TUnfold/TUnfoldIterativeEM.h"
#include "RooUnfold/TUnfold/TUnfoldSys.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldErrors.h"
#include "RooUnfoldFitHelpers.h"
#include "RooUnfoldGP.h"
#include "RooUnfoldHelpers.h"
#include "RooUnfoldHelpers.tpp"
#include "RooUnfoldIds.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldParms.h"
#include "RooUnfoldPoisson.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTH1Helpers.h"
#include "RooUnfoldTUnfold.h"
#include "TUnfold.h"
#include "TUnfoldBinning.h"
#include "TUnfoldBinningXML.h"
#include "TUnfoldDensity.h"
#include "TUnfoldIterativeEM.h"
#include "TUnfoldSys.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_RooUnfoldingcLcLRooFitHist(void *p = nullptr);
   static void *newArray_RooUnfoldingcLcLRooFitHist(Long_t size, void *p);
   static void delete_RooUnfoldingcLcLRooFitHist(void *p);
   static void deleteArray_RooUnfoldingcLcLRooFitHist(void *p);
   static void destruct_RooUnfoldingcLcLRooFitHist(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfolding::RooFitHist*)
   {
      ::RooUnfolding::RooFitHist *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfolding::RooFitHist >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfolding::RooFitHist", ::RooUnfolding::RooFitHist::Class_Version(), "RooUnfoldFitHelpers.h", 16,
                  typeid(::RooUnfolding::RooFitHist), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfolding::RooFitHist::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfolding::RooFitHist) );
      instance.SetNew(&new_RooUnfoldingcLcLRooFitHist);
      instance.SetNewArray(&newArray_RooUnfoldingcLcLRooFitHist);
      instance.SetDelete(&delete_RooUnfoldingcLcLRooFitHist);
      instance.SetDeleteArray(&deleteArray_RooUnfoldingcLcLRooFitHist);
      instance.SetDestructor(&destruct_RooUnfoldingcLcLRooFitHist);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfolding::RooFitHist*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfolding::RooFitHist*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfolding::RooFitHist*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldResponseTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldResponseTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldResponseTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldResponseTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldResponseTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldResponseTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldResponseTlETH1cOTH2gR(void *p);
   static void streamer_RooUnfoldResponseTlETH1cOTH2gR(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldResponseT<TH1,TH2>*)
   {
      ::RooUnfoldResponseT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldResponseT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldResponseT<TH1,TH2>", ::RooUnfoldResponseT<TH1,TH2>::Class_Version(), "RooUnfoldResponse.h", 28,
                  typeid(::RooUnfoldResponseT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldResponseTlETH1cOTH2gR_Dictionary, isa_proxy, 17,
                  sizeof(::RooUnfoldResponseT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldResponseTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldResponseTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldResponseTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldResponseTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldResponseTlETH1cOTH2gR);
      instance.SetStreamerFunc(&streamer_RooUnfoldResponseTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldResponseT<TH1,TH2>","RooUnfoldResponseT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldResponseT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldResponseT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldResponseT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldResponseTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldResponseT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldResponseTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldResponseTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void streamer_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldResponse.h", 28,
                  typeid(::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 17,
                  sizeof(::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetStreamerFunc(&streamer_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldResponseT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_RooUnfoldResponse(void *p = nullptr);
   static void *newArray_RooUnfoldResponse(Long_t size, void *p);
   static void delete_RooUnfoldResponse(void *p);
   static void deleteArray_RooUnfoldResponse(void *p);
   static void destruct_RooUnfoldResponse(void *p);
   static Long64_t merge_RooUnfoldResponse(void *obj, TCollection *coll,TFileMergeInfo *info);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldResponse*)
   {
      ::RooUnfoldResponse *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldResponse >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldResponse", ::RooUnfoldResponse::Class_Version(), "RooUnfoldResponse.h", 130,
                  typeid(::RooUnfoldResponse), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfoldResponse::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldResponse) );
      instance.SetNew(&new_RooUnfoldResponse);
      instance.SetNewArray(&newArray_RooUnfoldResponse);
      instance.SetDelete(&delete_RooUnfoldResponse);
      instance.SetDeleteArray(&deleteArray_RooUnfoldResponse);
      instance.SetDestructor(&destruct_RooUnfoldResponse);
      instance.SetMerge(&merge_RooUnfoldResponse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldResponse*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldResponse*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldResponse*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooFitUnfoldResponse(void *p = nullptr);
   static void *newArray_RooFitUnfoldResponse(Long_t size, void *p);
   static void delete_RooFitUnfoldResponse(void *p);
   static void deleteArray_RooFitUnfoldResponse(void *p);
   static void destruct_RooFitUnfoldResponse(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooFitUnfoldResponse*)
   {
      ::RooFitUnfoldResponse *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooFitUnfoldResponse >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooFitUnfoldResponse", ::RooFitUnfoldResponse::Class_Version(), "RooUnfoldResponse.h", 199,
                  typeid(::RooFitUnfoldResponse), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooFitUnfoldResponse::Dictionary, isa_proxy, 4,
                  sizeof(::RooFitUnfoldResponse) );
      instance.SetNew(&new_RooFitUnfoldResponse);
      instance.SetNewArray(&newArray_RooFitUnfoldResponse);
      instance.SetDelete(&delete_RooFitUnfoldResponse);
      instance.SetDeleteArray(&deleteArray_RooFitUnfoldResponse);
      instance.SetDestructor(&destruct_RooFitUnfoldResponse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooFitUnfoldResponse*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooFitUnfoldResponse*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooFitUnfoldResponse*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldTlETH1cOTH2gR(void *p);
   static void streamer_RooUnfoldTlETH1cOTH2gR(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldT<TH1,TH2>*)
   {
      ::RooUnfoldT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldT<TH1,TH2>", ::RooUnfoldT<TH1,TH2>::Class_Version(), "RooUnfold.h", 20,
                  typeid(::RooUnfoldT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldTlETH1cOTH2gR_Dictionary, isa_proxy, 17,
                  sizeof(::RooUnfoldT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldTlETH1cOTH2gR);
      instance.SetStreamerFunc(&streamer_RooUnfoldTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldT<TH1,TH2>","RooUnfold"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldT<TH1,TH2>","RooUnfoldT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void streamer_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfold.h", 20,
                  typeid(::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 17,
                  sizeof(::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetStreamerFunc(&streamer_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_RooUnfoldSpec(void *p);
   static void deleteArray_RooUnfoldSpec(void *p);
   static void destruct_RooUnfoldSpec(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldSpec*)
   {
      ::RooUnfoldSpec *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldSpec >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldSpec", ::RooUnfoldSpec::Class_Version(), "RooFitUnfold.h", 16,
                  typeid(::RooUnfoldSpec), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfoldSpec::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldSpec) );
      instance.SetDelete(&delete_RooUnfoldSpec);
      instance.SetDeleteArray(&deleteArray_RooUnfoldSpec);
      instance.SetDestructor(&destruct_RooUnfoldSpec);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldSpec*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldSpec*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSpec*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooUnfoldFunc(void *p = nullptr);
   static void *newArray_RooUnfoldFunc(Long_t size, void *p);
   static void delete_RooUnfoldFunc(void *p);
   static void deleteArray_RooUnfoldFunc(void *p);
   static void destruct_RooUnfoldFunc(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldFunc*)
   {
      ::RooUnfoldFunc *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldFunc >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldFunc", ::RooUnfoldFunc::Class_Version(), "RooFitUnfold.h", 130,
                  typeid(::RooUnfoldFunc), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfoldFunc::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldFunc) );
      instance.SetNew(&new_RooUnfoldFunc);
      instance.SetNewArray(&newArray_RooUnfoldFunc);
      instance.SetDelete(&delete_RooUnfoldFunc);
      instance.SetDeleteArray(&deleteArray_RooUnfoldFunc);
      instance.SetDestructor(&destruct_RooUnfoldFunc);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldFunc*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldFunc*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldFunc*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldV17(void *p = nullptr);
   static void *newArray_TUnfoldV17(Long_t size, void *p);
   static void delete_TUnfoldV17(void *p);
   static void deleteArray_TUnfoldV17(void *p);
   static void destruct_TUnfoldV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldV17*)
   {
      ::TUnfoldV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldV17", ::TUnfoldV17::Class_Version(), "TUnfold.h", 108,
                  typeid(::TUnfoldV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldV17) );
      instance.SetNew(&new_TUnfoldV17);
      instance.SetNewArray(&newArray_TUnfoldV17);
      instance.SetDelete(&delete_TUnfoldV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldV17);
      instance.SetDestructor(&destruct_TUnfoldV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldBinningV17(void *p = nullptr);
   static void *newArray_TUnfoldBinningV17(Long_t size, void *p);
   static void delete_TUnfoldBinningV17(void *p);
   static void deleteArray_TUnfoldBinningV17(void *p);
   static void destruct_TUnfoldBinningV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldBinningV17*)
   {
      ::TUnfoldBinningV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldBinningV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldBinningV17", ::TUnfoldBinningV17::Class_Version(), "TUnfoldBinning.h", 59,
                  typeid(::TUnfoldBinningV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldBinningV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldBinningV17) );
      instance.SetNew(&new_TUnfoldBinningV17);
      instance.SetNewArray(&newArray_TUnfoldBinningV17);
      instance.SetDelete(&delete_TUnfoldBinningV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldBinningV17);
      instance.SetDestructor(&destruct_TUnfoldBinningV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldBinningV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldBinningV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldBinningV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldBinningXMLV17(void *p = nullptr);
   static void *newArray_TUnfoldBinningXMLV17(Long_t size, void *p);
   static void delete_TUnfoldBinningXMLV17(void *p);
   static void deleteArray_TUnfoldBinningXMLV17(void *p);
   static void destruct_TUnfoldBinningXMLV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldBinningXMLV17*)
   {
      ::TUnfoldBinningXMLV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldBinningXMLV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldBinningXMLV17", ::TUnfoldBinningXMLV17::Class_Version(), "TUnfoldBinningXML.h", 60,
                  typeid(::TUnfoldBinningXMLV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldBinningXMLV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldBinningXMLV17) );
      instance.SetNew(&new_TUnfoldBinningXMLV17);
      instance.SetNewArray(&newArray_TUnfoldBinningXMLV17);
      instance.SetDelete(&delete_TUnfoldBinningXMLV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldBinningXMLV17);
      instance.SetDestructor(&destruct_TUnfoldBinningXMLV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldBinningXMLV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldBinningXMLV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldBinningXMLV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldSysV17(void *p = nullptr);
   static void *newArray_TUnfoldSysV17(Long_t size, void *p);
   static void delete_TUnfoldSysV17(void *p);
   static void deleteArray_TUnfoldSysV17(void *p);
   static void destruct_TUnfoldSysV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldSysV17*)
   {
      ::TUnfoldSysV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldSysV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldSysV17", ::TUnfoldSysV17::Class_Version(), "TUnfoldSys.h", 60,
                  typeid(::TUnfoldSysV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldSysV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldSysV17) );
      instance.SetNew(&new_TUnfoldSysV17);
      instance.SetNewArray(&newArray_TUnfoldSysV17);
      instance.SetDelete(&delete_TUnfoldSysV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldSysV17);
      instance.SetDestructor(&destruct_TUnfoldSysV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldSysV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldSysV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldSysV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldDensityV17(void *p = nullptr);
   static void *newArray_TUnfoldDensityV17(Long_t size, void *p);
   static void delete_TUnfoldDensityV17(void *p);
   static void deleteArray_TUnfoldDensityV17(void *p);
   static void destruct_TUnfoldDensityV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldDensityV17*)
   {
      ::TUnfoldDensityV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldDensityV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldDensityV17", ::TUnfoldDensityV17::Class_Version(), "TUnfoldDensity.h", 53,
                  typeid(::TUnfoldDensityV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldDensityV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldDensityV17) );
      instance.SetNew(&new_TUnfoldDensityV17);
      instance.SetNewArray(&newArray_TUnfoldDensityV17);
      instance.SetDelete(&delete_TUnfoldDensityV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldDensityV17);
      instance.SetDestructor(&destruct_TUnfoldDensityV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldDensityV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldDensityV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldDensityV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TUnfoldIterativeEMV17(void *p = nullptr);
   static void *newArray_TUnfoldIterativeEMV17(Long_t size, void *p);
   static void delete_TUnfoldIterativeEMV17(void *p);
   static void deleteArray_TUnfoldIterativeEMV17(void *p);
   static void destruct_TUnfoldIterativeEMV17(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TUnfoldIterativeEMV17*)
   {
      ::TUnfoldIterativeEMV17 *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TUnfoldIterativeEMV17 >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("TUnfoldIterativeEMV17", ::TUnfoldIterativeEMV17::Class_Version(), "TUnfoldIterativeEM.h", 47,
                  typeid(::TUnfoldIterativeEMV17), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TUnfoldIterativeEMV17::Dictionary, isa_proxy, 4,
                  sizeof(::TUnfoldIterativeEMV17) );
      instance.SetNew(&new_TUnfoldIterativeEMV17);
      instance.SetNewArray(&newArray_TUnfoldIterativeEMV17);
      instance.SetDelete(&delete_TUnfoldIterativeEMV17);
      instance.SetDeleteArray(&deleteArray_TUnfoldIterativeEMV17);
      instance.SetDestructor(&destruct_TUnfoldIterativeEMV17);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TUnfoldIterativeEMV17*)
   {
      return GenerateInitInstanceLocal(static_cast<::TUnfoldIterativeEMV17*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::TUnfoldIterativeEMV17*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldBayesTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldBayesTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldBayesTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldBayesTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldBayesTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldBayesTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldBayesTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldBayesT<TH1,TH2>*)
   {
      ::RooUnfoldBayesT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldBayesT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldBayesT<TH1,TH2>", ::RooUnfoldBayesT<TH1,TH2>::Class_Version(), "RooUnfoldBayes.h", 20,
                  typeid(::RooUnfoldBayesT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldBayesTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldBayesT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldBayesTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldBayesTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldBayesTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldBayesTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldBayesTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBayesT<TH1,TH2>","RooUnfoldBayes"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBayesT<TH1,TH2>","RooUnfoldBayesT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldBayesT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldBayesT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBayesT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldBayesTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBayesT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldBayesTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldBayesTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldBayes.h", 20,
                  typeid(::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldBayesT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldBinByBinTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldBinByBinTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldBinByBinTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldBinByBinTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldBinByBinTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldBinByBinTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldBinByBinTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldBinByBinT<TH1,TH2>*)
   {
      ::RooUnfoldBinByBinT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldBinByBinT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldBinByBinT<TH1,TH2>", ::RooUnfoldBinByBinT<TH1,TH2>::Class_Version(), "RooUnfoldBinByBin.h", 17,
                  typeid(::RooUnfoldBinByBinT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldBinByBinTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldBinByBinT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldBinByBinTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldBinByBinTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldBinByBinTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldBinByBinTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldBinByBinTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBinByBinT<TH1,TH2>","RooUnfoldBinByBin"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBinByBinT<TH1,TH2>","RooUnfoldBinByBinT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldBinByBinT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldBinByBinT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBinByBinT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldBinByBinTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBinByBinT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldBinByBinTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldBinByBinTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldBinByBin.h", 17,
                  typeid(::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldBinByBinT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_RooUnfoldErrors(void *p);
   static void deleteArray_RooUnfoldErrors(void *p);
   static void destruct_RooUnfoldErrors(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldErrors*)
   {
      ::RooUnfoldErrors *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldErrors >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldErrors", ::RooUnfoldErrors::Class_Version(), "RooUnfoldErrors.h", 22,
                  typeid(::RooUnfoldErrors), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfoldErrors::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldErrors) );
      instance.SetDelete(&delete_RooUnfoldErrors);
      instance.SetDeleteArray(&deleteArray_RooUnfoldErrors);
      instance.SetDestructor(&destruct_RooUnfoldErrors);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldErrors*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldErrors*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldErrors*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldGPTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldGPTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldGPTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldGPTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldGPTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldGPTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldGPTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldGPT<TH1,TH2>*)
   {
      ::RooUnfoldGPT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldGPT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldGPT<TH1,TH2>", ::RooUnfoldGPT<TH1,TH2>::Class_Version(), "RooUnfoldGP.h", 18,
                  typeid(::RooUnfoldGPT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldGPTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldGPT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldGPTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldGPTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldGPTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldGPTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldGPTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldGPT<TH1,TH2>","RooUnfoldGP"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldGPT<TH1,TH2>","RooUnfoldGPT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldGPT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldGPT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldGPT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldGPTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldGPT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldGPTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldGPTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldGP.h", 18,
                  typeid(::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldGPT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldIdsTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldIdsTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldIdsTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldIdsTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldIdsTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldIdsTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldIdsTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldIdsT<TH1,TH2>*)
   {
      ::RooUnfoldIdsT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldIdsT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldIdsT<TH1,TH2>", ::RooUnfoldIdsT<TH1,TH2>::Class_Version(), "RooUnfoldIds.h", 18,
                  typeid(::RooUnfoldIdsT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldIdsTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldIdsT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldIdsTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldIdsTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldIdsTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldIdsTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldIdsTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldIdsT<TH1,TH2>","RooUnfoldIds"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldIdsT<TH1,TH2>","RooUnfoldIdsT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldIdsT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldIdsT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldIdsT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldIdsTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldIdsT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldIdsTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldIdsTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldIds.h", 18,
                  typeid(::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldIdsT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldInvertTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldInvertTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldInvertTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldInvertTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldInvertTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldInvertTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldInvertTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldInvertT<TH1,TH2>*)
   {
      ::RooUnfoldInvertT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldInvertT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldInvertT<TH1,TH2>", ::RooUnfoldInvertT<TH1,TH2>::Class_Version(), "RooUnfoldInvert.h", 18,
                  typeid(::RooUnfoldInvertT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldInvertTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldInvertT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldInvertTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldInvertTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldInvertTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldInvertTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldInvertTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldInvertT<TH1,TH2>","RooUnfoldInvert"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldInvertT<TH1,TH2>","RooUnfoldInvertT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldInvertT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldInvertT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldInvertT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldInvertTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldInvertT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldInvertTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldInvertTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldInvert.h", 18,
                  typeid(::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldInvertT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_RooUnfoldParms(void *p = nullptr);
   static void *newArray_RooUnfoldParms(Long_t size, void *p);
   static void delete_RooUnfoldParms(void *p);
   static void deleteArray_RooUnfoldParms(void *p);
   static void destruct_RooUnfoldParms(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldParms*)
   {
      ::RooUnfoldParms *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldParms >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldParms", ::RooUnfoldParms::Class_Version(), "RooUnfoldParms.h", 21,
                  typeid(::RooUnfoldParms), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooUnfoldParms::Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldParms) );
      instance.SetNew(&new_RooUnfoldParms);
      instance.SetNewArray(&newArray_RooUnfoldParms);
      instance.SetDelete(&delete_RooUnfoldParms);
      instance.SetDeleteArray(&deleteArray_RooUnfoldParms);
      instance.SetDestructor(&destruct_RooUnfoldParms);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldParms*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldParms*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldParms*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldPoissonTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldPoissonTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldPoissonTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldPoissonTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldPoissonTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldPoissonTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldPoissonTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldPoissonT<TH1,TH2>*)
   {
      ::RooUnfoldPoissonT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldPoissonT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldPoissonT<TH1,TH2>", ::RooUnfoldPoissonT<TH1,TH2>::Class_Version(), "RooUnfoldPoisson.h", 22,
                  typeid(::RooUnfoldPoissonT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldPoissonTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldPoissonT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldPoissonTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldPoissonTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldPoissonTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldPoissonTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldPoissonTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldPoissonT<TH1,TH2>","RooUnfoldPoisson"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldPoissonT<TH1,TH2>","RooUnfoldPoissonT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldPoissonT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldPoissonT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldPoissonT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldPoissonTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldPoissonT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldPoissonTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldPoissonTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldPoisson.h", 22,
                  typeid(::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldPoissonT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldSvdTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldSvdTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldSvdTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldSvdTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldSvdTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldSvdTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldSvdTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldSvdT<TH1,TH2>*)
   {
      ::RooUnfoldSvdT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldSvdT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldSvdT<TH1,TH2>", ::RooUnfoldSvdT<TH1,TH2>::Class_Version(), "RooUnfoldSvd.h", 18,
                  typeid(::RooUnfoldSvdT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldSvdTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldSvdT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldSvdTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldSvdTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldSvdTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldSvdTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldSvdTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<TH1,TH2>","RooUnfoldSvd"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<TH1,TH2>","RooUnfoldSvdT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldSvdT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldSvdT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldSvdTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldSvdTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldSvdTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_Dictionary();
   static void RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_TClassManip(TClass*);
   static void delete_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p);
   static void deleteArray_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p);
   static void destruct_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*)
   {
      ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::RooUnfoldSvdT<TH1,TH2>::SVDUnfold));
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldSvdT<TH1,TH2>::SVDUnfold", "RooUnfoldSvd.h", 21,
                  typeid(::RooUnfoldSvdT<TH1,TH2>::SVDUnfold), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldSvdT<TH1,TH2>::SVDUnfold) );
      instance.SetDelete(&delete_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold);
      instance.SetDeleteArray(&deleteArray_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold);
      instance.SetDestructor(&destruct_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<TH1,TH2>::SVDUnfold","RooUnfoldSvd::SVDUnfold"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<TH1,TH2>::SVDUnfold","RooUnfoldSvdT<TH1, TH2>::SVDUnfold"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*>(nullptr))->GetClass();
      RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldSvd.h", 18,
                  typeid(::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldSvdT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_Dictionary();
   static void RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_TClassManip(TClass*);
   static void delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p);
   static void deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p);
   static void destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*)
   {
      ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold));
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold", "RooUnfoldSvd.h", 21,
                  typeid(::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold) );
      instance.SetDelete(&delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold);
      instance.SetDeleteArray(&deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold);
      instance.SetDestructor(&destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold","RooUnfoldSvdT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>::SVDUnfold"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*>(nullptr))->GetClass();
      RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldTUnfoldTlETH1cOTH2gR_Dictionary();
   static void RooUnfoldTUnfoldTlETH1cOTH2gR_TClassManip(TClass*);
   static void *new_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p = nullptr);
   static void *newArray_RooUnfoldTUnfoldTlETH1cOTH2gR(Long_t size, void *p);
   static void delete_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p);
   static void deleteArray_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p);
   static void destruct_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldTUnfoldT<TH1,TH2>*)
   {
      ::RooUnfoldTUnfoldT<TH1,TH2> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldTUnfoldT<TH1,TH2> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldTUnfoldT<TH1,TH2>", ::RooUnfoldTUnfoldT<TH1,TH2>::Class_Version(), "RooUnfoldTUnfold.h", 21,
                  typeid(::RooUnfoldTUnfoldT<TH1,TH2>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldTUnfoldTlETH1cOTH2gR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldTUnfoldT<TH1,TH2>) );
      instance.SetNew(&new_RooUnfoldTUnfoldTlETH1cOTH2gR);
      instance.SetNewArray(&newArray_RooUnfoldTUnfoldTlETH1cOTH2gR);
      instance.SetDelete(&delete_RooUnfoldTUnfoldTlETH1cOTH2gR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldTUnfoldTlETH1cOTH2gR);
      instance.SetDestructor(&destruct_RooUnfoldTUnfoldTlETH1cOTH2gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldTUnfoldT<TH1,TH2>","RooUnfoldTUnfold"));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldTUnfoldT<TH1,TH2>","RooUnfoldTUnfoldT<TH1, TH2>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldTUnfoldT<TH1,TH2>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldTUnfoldT<TH1,TH2>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldTUnfoldT<TH1,TH2>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldTUnfoldTlETH1cOTH2gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldTUnfoldT<TH1,TH2>*>(nullptr))->GetClass();
      RooUnfoldTUnfoldTlETH1cOTH2gR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldTUnfoldTlETH1cOTH2gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary();
   static void RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass*);
   static void *new_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p = nullptr);
   static void *newArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t size, void *p);
   static void delete_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void deleteArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);
   static void destruct_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Version(), "RooUnfoldTUnfold.h", 21,
                  typeid(::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary, isa_proxy, 4,
                  sizeof(::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>) );
      instance.SetNew(&new_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetNewArray(&newArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDelete(&delete_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDeleteArray(&deleteArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);
      instance.SetDestructor(&destruct_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>","RooUnfoldTUnfoldT<RooUnfolding::RooFitHist, RooUnfolding::RooFitHist>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)
   {
      return GenerateInitInstanceLocal(static_cast<::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(nullptr))->GetClass();
      RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(theClass);
   return theClass;
   }

   static void RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace RooUnfolding {
//______________________________________________________________________________
atomic_TClass_ptr RooFitHist::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFitHist::Class_Name()
{
   return "RooUnfolding::RooFitHist";
}

//______________________________________________________________________________
const char *RooFitHist::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfolding::RooFitHist*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooFitHist::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfolding::RooFitHist*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFitHist::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfolding::RooFitHist*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFitHist::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfolding::RooFitHist*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace RooUnfolding
//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldResponseT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldResponseT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldResponseT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldResponseT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldResponseT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldResponseT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldResponseT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooUnfoldResponse::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooUnfoldResponse::Class_Name()
{
   return "RooUnfoldResponse";
}

//______________________________________________________________________________
const char *RooUnfoldResponse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponse*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooUnfoldResponse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponse*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooUnfoldResponse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponse*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooUnfoldResponse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldResponse*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooFitUnfoldResponse::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooFitUnfoldResponse::Class_Name()
{
   return "RooFitUnfoldResponse";
}

//______________________________________________________________________________
const char *RooFitUnfoldResponse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFitUnfoldResponse*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooFitUnfoldResponse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooFitUnfoldResponse*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooFitUnfoldResponse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFitUnfoldResponse*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooFitUnfoldResponse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooFitUnfoldResponse*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooUnfoldSpec::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooUnfoldSpec::Class_Name()
{
   return "RooUnfoldSpec";
}

//______________________________________________________________________________
const char *RooUnfoldSpec::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSpec*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooUnfoldSpec::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSpec*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooUnfoldSpec::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSpec*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooUnfoldSpec::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSpec*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooUnfoldFunc::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooUnfoldFunc::Class_Name()
{
   return "RooUnfoldFunc";
}

//______________________________________________________________________________
const char *RooUnfoldFunc::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldFunc*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooUnfoldFunc::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldFunc*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooUnfoldFunc::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldFunc*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooUnfoldFunc::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldFunc*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldV17::Class_Name()
{
   return "TUnfoldV17";
}

//______________________________________________________________________________
const char *TUnfoldV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldBinningV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldBinningV17::Class_Name()
{
   return "TUnfoldBinningV17";
}

//______________________________________________________________________________
const char *TUnfoldBinningV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldBinningV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldBinningV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldBinningV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldBinningXMLV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldBinningXMLV17::Class_Name()
{
   return "TUnfoldBinningXMLV17";
}

//______________________________________________________________________________
const char *TUnfoldBinningXMLV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningXMLV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldBinningXMLV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningXMLV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldBinningXMLV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningXMLV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldBinningXMLV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldBinningXMLV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldSysV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldSysV17::Class_Name()
{
   return "TUnfoldSysV17";
}

//______________________________________________________________________________
const char *TUnfoldSysV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldSysV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldSysV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldSysV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldSysV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldSysV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldSysV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldSysV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldDensityV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldDensityV17::Class_Name()
{
   return "TUnfoldDensityV17";
}

//______________________________________________________________________________
const char *TUnfoldDensityV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldDensityV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldDensityV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldDensityV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldDensityV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldDensityV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldDensityV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldDensityV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TUnfoldIterativeEMV17::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *TUnfoldIterativeEMV17::Class_Name()
{
   return "TUnfoldIterativeEMV17";
}

//______________________________________________________________________________
const char *TUnfoldIterativeEMV17::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldIterativeEMV17*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int TUnfoldIterativeEMV17::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldIterativeEMV17*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TUnfoldIterativeEMV17::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldIterativeEMV17*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TUnfoldIterativeEMV17::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TUnfoldIterativeEMV17*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldBayesT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldBayesT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldBayesT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldBayesT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldBayesT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBayesT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBayesT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldBinByBinT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldBinByBinT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldBinByBinT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldBinByBinT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldBinByBinT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBinByBinT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBinByBinT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooUnfoldErrors::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooUnfoldErrors::Class_Name()
{
   return "RooUnfoldErrors";
}

//______________________________________________________________________________
const char *RooUnfoldErrors::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldErrors*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooUnfoldErrors::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldErrors*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooUnfoldErrors::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldErrors*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooUnfoldErrors::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldErrors*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldGPT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldGPT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldGPT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldGPT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldGPT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldGPT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldGPT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldIdsT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldIdsT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldIdsT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldIdsT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldIdsT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldIdsT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldIdsT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldInvertT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldInvertT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldInvertT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldInvertT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldInvertT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldInvertT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldInvertT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooUnfoldParms::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RooUnfoldParms::Class_Name()
{
   return "RooUnfoldParms";
}

//______________________________________________________________________________
const char *RooUnfoldParms::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldParms*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RooUnfoldParms::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldParms*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooUnfoldParms::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldParms*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooUnfoldParms::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldParms*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldPoissonT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldPoissonT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldPoissonT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldPoissonT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldPoissonT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldPoissonT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldPoissonT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldSvdT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldSvdT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldSvdT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldSvdT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldSvdT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldSvdT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldSvdT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldTUnfoldT<TH1,TH2>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldTUnfoldT<TH1,TH2>::Class_Name()
{
   return "RooUnfoldTUnfoldT<TH1,TH2>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldTUnfoldT<TH1,TH2>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<TH1,TH2>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldTUnfoldT<TH1,TH2>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<TH1,TH2>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldTUnfoldT<TH1,TH2>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<TH1,TH2>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldTUnfoldT<TH1,TH2>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<TH1,TH2>*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class_Name()
{
   return "RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>";
}

//______________________________________________________________________________
template <> const char *RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)nullptr)->GetClass(); }
   return fgIsA;
}

namespace RooUnfolding {
//______________________________________________________________________________
void RooFitHist::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfolding::RooFitHist.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfolding::RooFitHist::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfolding::RooFitHist::Class(),this);
   }
}

} // namespace RooUnfolding
namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldingcLcLRooFitHist(void *p) {
      return  p ? new(p) ::RooUnfolding::RooFitHist : new ::RooUnfolding::RooFitHist;
   }
   static void *newArray_RooUnfoldingcLcLRooFitHist(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfolding::RooFitHist[nElements] : new ::RooUnfolding::RooFitHist[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldingcLcLRooFitHist(void *p) {
      delete (static_cast<::RooUnfolding::RooFitHist*>(p));
   }
   static void deleteArray_RooUnfoldingcLcLRooFitHist(void *p) {
      delete [] (static_cast<::RooUnfolding::RooFitHist*>(p));
   }
   static void destruct_RooUnfoldingcLcLRooFitHist(void *p) {
      typedef ::RooUnfolding::RooFitHist current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfolding::RooFitHist

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldResponseTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldResponseT<TH1,TH2> : new ::RooUnfoldResponseT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldResponseTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldResponseT<TH1,TH2>[nElements] : new ::RooUnfoldResponseT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldResponseTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldResponseT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldResponseTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldResponseT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldResponseTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldResponseT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooUnfoldResponseTlETH1cOTH2gR(TBuffer &buf, void *obj) {
      ((::RooUnfoldResponseT<TH1,TH2>*)obj)->::RooUnfoldResponseT<TH1,TH2>::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooUnfoldResponseT<TH1,TH2>

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooUnfoldResponseTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(TBuffer &buf, void *obj) {
      ((::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)obj)->::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
void RooUnfoldResponse::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldResponse.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldResponse::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldResponse::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldResponse(void *p) {
      return  p ? new(p) ::RooUnfoldResponse : new ::RooUnfoldResponse;
   }
   static void *newArray_RooUnfoldResponse(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldResponse[nElements] : new ::RooUnfoldResponse[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldResponse(void *p) {
      delete (static_cast<::RooUnfoldResponse*>(p));
   }
   static void deleteArray_RooUnfoldResponse(void *p) {
      delete [] (static_cast<::RooUnfoldResponse*>(p));
   }
   static void destruct_RooUnfoldResponse(void *p) {
      typedef ::RooUnfoldResponse current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around the merge function.
   static Long64_t  merge_RooUnfoldResponse(void *obj,TCollection *coll,TFileMergeInfo *) {
      return ((::RooUnfoldResponse*)obj)->Merge(coll);
   }
} // end of namespace ROOT for class ::RooUnfoldResponse

//______________________________________________________________________________
void RooFitUnfoldResponse::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooFitUnfoldResponse.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooFitUnfoldResponse::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooFitUnfoldResponse::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooFitUnfoldResponse(void *p) {
      return  p ? new(p) ::RooFitUnfoldResponse : new ::RooFitUnfoldResponse;
   }
   static void *newArray_RooFitUnfoldResponse(Long_t nElements, void *p) {
      return p ? new(p) ::RooFitUnfoldResponse[nElements] : new ::RooFitUnfoldResponse[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooFitUnfoldResponse(void *p) {
      delete (static_cast<::RooFitUnfoldResponse*>(p));
   }
   static void deleteArray_RooFitUnfoldResponse(void *p) {
      delete [] (static_cast<::RooFitUnfoldResponse*>(p));
   }
   static void destruct_RooFitUnfoldResponse(void *p) {
      typedef ::RooFitUnfoldResponse current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooFitUnfoldResponse

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldT<TH1,TH2> : new ::RooUnfoldT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldT<TH1,TH2>[nElements] : new ::RooUnfoldT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooUnfoldTlETH1cOTH2gR(TBuffer &buf, void *obj) {
      ((::RooUnfoldT<TH1,TH2>*)obj)->::RooUnfoldT<TH1,TH2>::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooUnfoldT<TH1,TH2>

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(TBuffer &buf, void *obj) {
      ((::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*)obj)->::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
void RooUnfoldSpec::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldSpec.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldSpec::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldSpec::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RooUnfoldSpec(void *p) {
      delete (static_cast<::RooUnfoldSpec*>(p));
   }
   static void deleteArray_RooUnfoldSpec(void *p) {
      delete [] (static_cast<::RooUnfoldSpec*>(p));
   }
   static void destruct_RooUnfoldSpec(void *p) {
      typedef ::RooUnfoldSpec current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldSpec

//______________________________________________________________________________
void RooUnfoldFunc::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldFunc.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldFunc::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldFunc::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldFunc(void *p) {
      return  p ? new(p) ::RooUnfoldFunc : new ::RooUnfoldFunc;
   }
   static void *newArray_RooUnfoldFunc(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldFunc[nElements] : new ::RooUnfoldFunc[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldFunc(void *p) {
      delete (static_cast<::RooUnfoldFunc*>(p));
   }
   static void deleteArray_RooUnfoldFunc(void *p) {
      delete [] (static_cast<::RooUnfoldFunc*>(p));
   }
   static void destruct_RooUnfoldFunc(void *p) {
      typedef ::RooUnfoldFunc current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldFunc

//______________________________________________________________________________
void TUnfoldV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldV17(void *p) {
      return  p ? new(p) ::TUnfoldV17 : new ::TUnfoldV17;
   }
   static void *newArray_TUnfoldV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldV17[nElements] : new ::TUnfoldV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldV17(void *p) {
      delete (static_cast<::TUnfoldV17*>(p));
   }
   static void deleteArray_TUnfoldV17(void *p) {
      delete [] (static_cast<::TUnfoldV17*>(p));
   }
   static void destruct_TUnfoldV17(void *p) {
      typedef ::TUnfoldV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldV17

//______________________________________________________________________________
void TUnfoldBinningV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldBinningV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldBinningV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldBinningV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldBinningV17(void *p) {
      return  p ? new(p) ::TUnfoldBinningV17 : new ::TUnfoldBinningV17;
   }
   static void *newArray_TUnfoldBinningV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldBinningV17[nElements] : new ::TUnfoldBinningV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldBinningV17(void *p) {
      delete (static_cast<::TUnfoldBinningV17*>(p));
   }
   static void deleteArray_TUnfoldBinningV17(void *p) {
      delete [] (static_cast<::TUnfoldBinningV17*>(p));
   }
   static void destruct_TUnfoldBinningV17(void *p) {
      typedef ::TUnfoldBinningV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldBinningV17

//______________________________________________________________________________
void TUnfoldBinningXMLV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldBinningXMLV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldBinningXMLV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldBinningXMLV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldBinningXMLV17(void *p) {
      return  p ? new(p) ::TUnfoldBinningXMLV17 : new ::TUnfoldBinningXMLV17;
   }
   static void *newArray_TUnfoldBinningXMLV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldBinningXMLV17[nElements] : new ::TUnfoldBinningXMLV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldBinningXMLV17(void *p) {
      delete (static_cast<::TUnfoldBinningXMLV17*>(p));
   }
   static void deleteArray_TUnfoldBinningXMLV17(void *p) {
      delete [] (static_cast<::TUnfoldBinningXMLV17*>(p));
   }
   static void destruct_TUnfoldBinningXMLV17(void *p) {
      typedef ::TUnfoldBinningXMLV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldBinningXMLV17

//______________________________________________________________________________
void TUnfoldSysV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldSysV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldSysV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldSysV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldSysV17(void *p) {
      return  p ? new(p) ::TUnfoldSysV17 : new ::TUnfoldSysV17;
   }
   static void *newArray_TUnfoldSysV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldSysV17[nElements] : new ::TUnfoldSysV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldSysV17(void *p) {
      delete (static_cast<::TUnfoldSysV17*>(p));
   }
   static void deleteArray_TUnfoldSysV17(void *p) {
      delete [] (static_cast<::TUnfoldSysV17*>(p));
   }
   static void destruct_TUnfoldSysV17(void *p) {
      typedef ::TUnfoldSysV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldSysV17

//______________________________________________________________________________
void TUnfoldDensityV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldDensityV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldDensityV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldDensityV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldDensityV17(void *p) {
      return  p ? new(p) ::TUnfoldDensityV17 : new ::TUnfoldDensityV17;
   }
   static void *newArray_TUnfoldDensityV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldDensityV17[nElements] : new ::TUnfoldDensityV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldDensityV17(void *p) {
      delete (static_cast<::TUnfoldDensityV17*>(p));
   }
   static void deleteArray_TUnfoldDensityV17(void *p) {
      delete [] (static_cast<::TUnfoldDensityV17*>(p));
   }
   static void destruct_TUnfoldDensityV17(void *p) {
      typedef ::TUnfoldDensityV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldDensityV17

//______________________________________________________________________________
void TUnfoldIterativeEMV17::Streamer(TBuffer &R__b)
{
   // Stream an object of class TUnfoldIterativeEMV17.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TUnfoldIterativeEMV17::Class(),this);
   } else {
      R__b.WriteClassBuffer(TUnfoldIterativeEMV17::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TUnfoldIterativeEMV17(void *p) {
      return  p ? new(p) ::TUnfoldIterativeEMV17 : new ::TUnfoldIterativeEMV17;
   }
   static void *newArray_TUnfoldIterativeEMV17(Long_t nElements, void *p) {
      return p ? new(p) ::TUnfoldIterativeEMV17[nElements] : new ::TUnfoldIterativeEMV17[nElements];
   }
   // Wrapper around operator delete
   static void delete_TUnfoldIterativeEMV17(void *p) {
      delete (static_cast<::TUnfoldIterativeEMV17*>(p));
   }
   static void deleteArray_TUnfoldIterativeEMV17(void *p) {
      delete [] (static_cast<::TUnfoldIterativeEMV17*>(p));
   }
   static void destruct_TUnfoldIterativeEMV17(void *p) {
      typedef ::TUnfoldIterativeEMV17 current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::TUnfoldIterativeEMV17

//______________________________________________________________________________
template <> void RooUnfoldBayesT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldBayesT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldBayesT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldBayesT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldBayesTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldBayesT<TH1,TH2> : new ::RooUnfoldBayesT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldBayesTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldBayesT<TH1,TH2>[nElements] : new ::RooUnfoldBayesT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldBayesTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldBayesT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldBayesTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldBayesT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldBayesTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldBayesT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldBayesT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldBayesTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
template <> void RooUnfoldBinByBinT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldBinByBinT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldBinByBinT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldBinByBinT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldBinByBinTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldBinByBinT<TH1,TH2> : new ::RooUnfoldBinByBinT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldBinByBinTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldBinByBinT<TH1,TH2>[nElements] : new ::RooUnfoldBinByBinT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldBinByBinTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldBinByBinT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldBinByBinTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldBinByBinT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldBinByBinTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldBinByBinT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldBinByBinT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldBinByBinTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
void RooUnfoldErrors::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldErrors.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldErrors::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldErrors::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RooUnfoldErrors(void *p) {
      delete (static_cast<::RooUnfoldErrors*>(p));
   }
   static void deleteArray_RooUnfoldErrors(void *p) {
      delete [] (static_cast<::RooUnfoldErrors*>(p));
   }
   static void destruct_RooUnfoldErrors(void *p) {
      typedef ::RooUnfoldErrors current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldErrors

//______________________________________________________________________________
template <> void RooUnfoldGPT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldGPT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldGPT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldGPT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldGPTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldGPT<TH1,TH2> : new ::RooUnfoldGPT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldGPTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldGPT<TH1,TH2>[nElements] : new ::RooUnfoldGPT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldGPTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldGPT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldGPTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldGPT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldGPTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldGPT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldGPT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldGPTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
template <> void RooUnfoldIdsT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldIdsT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldIdsT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldIdsT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldIdsTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldIdsT<TH1,TH2> : new ::RooUnfoldIdsT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldIdsTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldIdsT<TH1,TH2>[nElements] : new ::RooUnfoldIdsT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldIdsTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldIdsT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldIdsTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldIdsT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldIdsTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldIdsT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldIdsT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldIdsTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
template <> void RooUnfoldInvertT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldInvertT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldInvertT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldInvertT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldInvertTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldInvertT<TH1,TH2> : new ::RooUnfoldInvertT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldInvertTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldInvertT<TH1,TH2>[nElements] : new ::RooUnfoldInvertT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldInvertTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldInvertT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldInvertTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldInvertT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldInvertTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldInvertT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldInvertT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldInvertTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
void RooUnfoldParms::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldParms.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldParms::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldParms::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldParms(void *p) {
      return  p ? new(p) ::RooUnfoldParms : new ::RooUnfoldParms;
   }
   static void *newArray_RooUnfoldParms(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldParms[nElements] : new ::RooUnfoldParms[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldParms(void *p) {
      delete (static_cast<::RooUnfoldParms*>(p));
   }
   static void deleteArray_RooUnfoldParms(void *p) {
      delete [] (static_cast<::RooUnfoldParms*>(p));
   }
   static void destruct_RooUnfoldParms(void *p) {
      typedef ::RooUnfoldParms current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldParms

//______________________________________________________________________________
template <> void RooUnfoldPoissonT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldPoissonT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldPoissonT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldPoissonT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldPoissonTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldPoissonT<TH1,TH2> : new ::RooUnfoldPoissonT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldPoissonTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldPoissonT<TH1,TH2>[nElements] : new ::RooUnfoldPoissonT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldPoissonTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldPoissonT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldPoissonTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldPoissonT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldPoissonTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldPoissonT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldPoissonT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldPoissonTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

//______________________________________________________________________________
template <> void RooUnfoldSvdT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldSvdT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldSvdT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldSvdT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldSvdTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldSvdT<TH1,TH2> : new ::RooUnfoldSvdT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldSvdTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldSvdT<TH1,TH2>[nElements] : new ::RooUnfoldSvdT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldSvdTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldSvdT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldSvdTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldSvdT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldSvdTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldSvdT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldSvdT<TH1,TH2>

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p) {
      delete (static_cast<::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*>(p));
   }
   static void deleteArray_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p) {
      delete [] (static_cast<::RooUnfoldSvdT<TH1,TH2>::SVDUnfold*>(p));
   }
   static void destruct_RooUnfoldSvdTlETH1cOTH2gRcLcLSVDUnfold(void *p) {
      typedef ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldSvdT<TH1,TH2>::SVDUnfold

//______________________________________________________________________________
template <> void RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

namespace ROOT {
   // Wrapper around operator delete
   static void delete_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p) {
      delete (static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*>(p));
   }
   static void deleteArray_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p) {
      delete [] (static_cast<::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold*>(p));
   }
   static void destruct_RooUnfoldSvdTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgRcLcLSVDUnfold(void *p) {
      typedef ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold

//______________________________________________________________________________
template <> void RooUnfoldTUnfoldT<TH1,TH2>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldTUnfoldT<TH1,TH2>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldTUnfoldT<TH1,TH2>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldTUnfoldT<TH1,TH2>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p) {
      return  p ? new(p) ::RooUnfoldTUnfoldT<TH1,TH2> : new ::RooUnfoldTUnfoldT<TH1,TH2>;
   }
   static void *newArray_RooUnfoldTUnfoldTlETH1cOTH2gR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldTUnfoldT<TH1,TH2>[nElements] : new ::RooUnfoldTUnfoldT<TH1,TH2>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p) {
      delete (static_cast<::RooUnfoldTUnfoldT<TH1,TH2>*>(p));
   }
   static void deleteArray_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p) {
      delete [] (static_cast<::RooUnfoldTUnfoldT<TH1,TH2>*>(p));
   }
   static void destruct_RooUnfoldTUnfoldTlETH1cOTH2gR(void *p) {
      typedef ::RooUnfoldTUnfoldT<TH1,TH2> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldTUnfoldT<TH1,TH2>

//______________________________________________________________________________
template <> void RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   } else {
      R__b.WriteClassBuffer(RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      return  p ? new(p) ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> : new ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>;
   }
   static void *newArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(Long_t nElements, void *p) {
      return p ? new(p) ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements] : new ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete (static_cast<::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void deleteArray_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      delete [] (static_cast<::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>*>(p));
   }
   static void destruct_RooUnfoldTUnfoldTlERooUnfoldingcLcLRooFitHistcORooUnfoldingcLcLRooFitHistgR(void *p) {
      typedef ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>

namespace ROOT {
   static TClass *vectorlERooRealVarmUgR_Dictionary();
   static void vectorlERooRealVarmUgR_TClassManip(TClass*);
   static void *new_vectorlERooRealVarmUgR(void *p = nullptr);
   static void *newArray_vectorlERooRealVarmUgR(Long_t size, void *p);
   static void delete_vectorlERooRealVarmUgR(void *p);
   static void deleteArray_vectorlERooRealVarmUgR(void *p);
   static void destruct_vectorlERooRealVarmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RooRealVar*>*)
   {
      vector<RooRealVar*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RooRealVar*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RooRealVar*>", -2, "vector", 389,
                  typeid(vector<RooRealVar*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERooRealVarmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<RooRealVar*>) );
      instance.SetNew(&new_vectorlERooRealVarmUgR);
      instance.SetNewArray(&newArray_vectorlERooRealVarmUgR);
      instance.SetDelete(&delete_vectorlERooRealVarmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlERooRealVarmUgR);
      instance.SetDestructor(&destruct_vectorlERooRealVarmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RooRealVar*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<RooRealVar*>","std::vector<RooRealVar*, std::allocator<RooRealVar*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<RooRealVar*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERooRealVarmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<RooRealVar*>*>(nullptr))->GetClass();
      vectorlERooRealVarmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERooRealVarmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERooRealVarmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RooRealVar*> : new vector<RooRealVar*>;
   }
   static void *newArray_vectorlERooRealVarmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RooRealVar*>[nElements] : new vector<RooRealVar*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERooRealVarmUgR(void *p) {
      delete (static_cast<vector<RooRealVar*>*>(p));
   }
   static void deleteArray_vectorlERooRealVarmUgR(void *p) {
      delete [] (static_cast<vector<RooRealVar*>*>(p));
   }
   static void destruct_vectorlERooRealVarmUgR(void *p) {
      typedef vector<RooRealVar*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<RooRealVar*>

namespace ROOT {
   static TClass *vectorlERooAbsArgmUgR_Dictionary();
   static void vectorlERooAbsArgmUgR_TClassManip(TClass*);
   static void *new_vectorlERooAbsArgmUgR(void *p = nullptr);
   static void *newArray_vectorlERooAbsArgmUgR(Long_t size, void *p);
   static void delete_vectorlERooAbsArgmUgR(void *p);
   static void deleteArray_vectorlERooAbsArgmUgR(void *p);
   static void destruct_vectorlERooAbsArgmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RooAbsArg*>*)
   {
      vector<RooAbsArg*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RooAbsArg*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RooAbsArg*>", -2, "vector", 389,
                  typeid(vector<RooAbsArg*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERooAbsArgmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<RooAbsArg*>) );
      instance.SetNew(&new_vectorlERooAbsArgmUgR);
      instance.SetNewArray(&newArray_vectorlERooAbsArgmUgR);
      instance.SetDelete(&delete_vectorlERooAbsArgmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlERooAbsArgmUgR);
      instance.SetDestructor(&destruct_vectorlERooAbsArgmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RooAbsArg*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<RooAbsArg*>","std::vector<RooAbsArg*, std::allocator<RooAbsArg*> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<RooAbsArg*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERooAbsArgmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<RooAbsArg*>*>(nullptr))->GetClass();
      vectorlERooAbsArgmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERooAbsArgmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERooAbsArgmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RooAbsArg*> : new vector<RooAbsArg*>;
   }
   static void *newArray_vectorlERooAbsArgmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RooAbsArg*>[nElements] : new vector<RooAbsArg*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERooAbsArgmUgR(void *p) {
      delete (static_cast<vector<RooAbsArg*>*>(p));
   }
   static void deleteArray_vectorlERooAbsArgmUgR(void *p) {
      delete [] (static_cast<vector<RooAbsArg*>*>(p));
   }
   static void destruct_vectorlERooAbsArgmUgR(void *p) {
      typedef vector<RooAbsArg*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<RooAbsArg*>

namespace {
  void TriggerDictionaryInitialization_libRooUnfold_Impl() {
    static const char* headers[] = {
"RooFitUnfold.h",
"RooUnfold.h",
"RooUnfold/TUnfold/TUnfold.h",
"RooUnfold/TUnfold/TUnfoldBinning.h",
"RooUnfold/TUnfold/TUnfoldBinningXML.h",
"RooUnfold/TUnfold/TUnfoldDensity.h",
"RooUnfold/TUnfold/TUnfoldIterativeEM.h",
"RooUnfold/TUnfold/TUnfoldSys.h",
"RooUnfoldBayes.h",
"RooUnfoldBinByBin.h",
"RooUnfoldErrors.h",
"RooUnfoldFitHelpers.h",
"RooUnfoldGP.h",
"RooUnfoldHelpers.h",
"RooUnfoldIds.h",
"RooUnfoldInvert.h",
"RooUnfoldParms.h",
"RooUnfoldPoisson.h",
"RooUnfoldResponse.h",
"RooUnfoldSvd.h",
"RooUnfoldTH1Helpers.h",
"RooUnfoldTUnfold.h",
"TUnfold.h",
"TUnfoldBinning.h",
"TUnfoldBinningXML.h",
"TUnfoldDensity.h",
"TUnfoldIterativeEM.h",
"TUnfoldSys.h",
nullptr
    };
    static const char* includePaths[] = {
"/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/src",
"/cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/almalinux9-gcc11/local/root/6.30.04/include",
"/work/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold",
"/cvmfs/oasis.opensciencegrid.org/jlab/hallb/clas12/sw/almalinux9-gcc11/local/root/6.30.04/include/",
"/w/hallb-scshelf2102/clas12/jsalvg/RGA-Analysis/inb/P/include/RooUnfold/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libRooUnfold dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace RooUnfolding{class __attribute__((annotate("$clingAutoload$RooUnfoldFitHelpers.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooFitHist;}
class __attribute__((annotate("$clingAutoload$TH1.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  TH1;
class __attribute__((annotate("$clingAutoload$TH2.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  TH2;
template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldResponse.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooUnfoldResponseT;

class __attribute__((annotate("$clingAutoload$RooUnfoldResponse.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooUnfoldResponse;
class __attribute__((annotate("$clingAutoload$RooUnfoldResponse.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooFitUnfoldResponse;
template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfold.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooUnfoldT;

class __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooUnfoldSpec;
class __attribute__((annotate("$clingAutoload$RooFitUnfold.h")))  RooUnfoldFunc;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfold.h")))  TUnfoldV17;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldBinning.h")))  TUnfoldBinningV17;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldBinningXML.h")))  TUnfoldBinningXMLV17;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldSys.h")))  __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldDensity.h")))  TUnfoldSysV17;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldDensity.h")))  TUnfoldDensityV17;
class __attribute__((annotate("$clingAutoload$RooUnfold/TUnfold/TUnfoldIterativeEM.h")))  TUnfoldIterativeEMV17;
template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldBayes.h")))  RooUnfoldBayesT;

template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldBinByBin.h")))  RooUnfoldBinByBinT;

class __attribute__((annotate("$clingAutoload$RooUnfoldErrors.h")))  RooUnfoldErrors;
template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldGP.h")))  RooUnfoldGPT;

template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldIds.h")))  RooUnfoldIdsT;

template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldInvert.h")))  RooUnfoldInvertT;

class __attribute__((annotate("$clingAutoload$RooUnfoldParms.h")))  RooUnfoldParms;
template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldPoisson.h")))  RooUnfoldPoissonT;

template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldSvd.h")))  RooUnfoldSvdT;

template <class Hist, class Hist2D> class __attribute__((annotate("$clingAutoload$RooUnfoldTUnfold.h")))  RooUnfoldTUnfoldT;

typedef RooUnfoldT<TH1, TH2> RooUnfold __attribute__((annotate("$clingAutoload$RooUnfold.h")))  __attribute__((annotate("$clingAutoload$RooFitUnfold.h"))) ;
typedef RooUnfoldBayesT<TH1, TH2> RooUnfoldBayes __attribute__((annotate("$clingAutoload$RooUnfoldBayes.h"))) ;
typedef RooUnfoldBinByBinT<TH1, TH2> RooUnfoldBinByBin __attribute__((annotate("$clingAutoload$RooUnfoldBinByBin.h"))) ;
typedef RooUnfoldGPT<TH1, TH2> RooUnfoldGP __attribute__((annotate("$clingAutoload$RooUnfoldGP.h"))) ;
typedef RooUnfoldIdsT<TH1, TH2> RooUnfoldIds __attribute__((annotate("$clingAutoload$RooUnfoldIds.h"))) ;
typedef RooUnfoldInvertT<TH1, TH2> RooUnfoldInvert __attribute__((annotate("$clingAutoload$RooUnfoldInvert.h"))) ;
typedef RooUnfoldPoissonT<TH1, TH2> RooUnfoldPoisson __attribute__((annotate("$clingAutoload$RooUnfoldPoisson.h"))) ;
typedef RooUnfoldSvdT<TH1, TH2> RooUnfoldSvd __attribute__((annotate("$clingAutoload$RooUnfoldSvd.h"))) ;
typedef RooUnfoldTUnfoldT<TH1, TH2> RooUnfoldTUnfold __attribute__((annotate("$clingAutoload$RooUnfoldTUnfold.h"))) ;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libRooUnfold dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "RooFitUnfold.h"
#include "RooUnfold.h"
#include "RooUnfold/TUnfold/TUnfold.h"
#include "RooUnfold/TUnfold/TUnfoldBinning.h"
#include "RooUnfold/TUnfold/TUnfoldBinningXML.h"
#include "RooUnfold/TUnfold/TUnfoldDensity.h"
#include "RooUnfold/TUnfold/TUnfoldIterativeEM.h"
#include "RooUnfold/TUnfold/TUnfoldSys.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldErrors.h"
#include "RooUnfoldFitHelpers.h"
#include "RooUnfoldGP.h"
#include "RooUnfoldHelpers.h"
#include "RooUnfoldIds.h"
#include "RooUnfoldInvert.h"
#include "RooUnfoldParms.h"
#include "RooUnfoldPoisson.h"
#include "RooUnfoldResponse.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldTH1Helpers.h"
#include "RooUnfoldTUnfold.h"
#include "TUnfold.h"
#include "TUnfoldBinning.h"
#include "TUnfoldBinningXML.h"
#include "TUnfoldDensity.h"
#include "TUnfoldIterativeEM.h"
#include "TUnfoldSys.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"RooFitUnfoldResponse", payloadCode, "@",
"RooUnfold", payloadCode, "@",
"RooUnfoldBayes", payloadCode, "@",
"RooUnfoldBayesT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldBayesT<TH1,TH2>", payloadCode, "@",
"RooUnfoldBinByBin", payloadCode, "@",
"RooUnfoldBinByBinT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldBinByBinT<TH1,TH2>", payloadCode, "@",
"RooUnfoldErrors", payloadCode, "@",
"RooUnfoldFunc", payloadCode, "@",
"RooUnfoldGP", payloadCode, "@",
"RooUnfoldGPT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldGPT<TH1,TH2>", payloadCode, "@",
"RooUnfoldIds", payloadCode, "@",
"RooUnfoldIdsT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldIdsT<TH1,TH2>", payloadCode, "@",
"RooUnfoldInvert", payloadCode, "@",
"RooUnfoldInvertT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldInvertT<TH1,TH2>", payloadCode, "@",
"RooUnfoldParms", payloadCode, "@",
"RooUnfoldPoisson", payloadCode, "@",
"RooUnfoldPoissonT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldPoissonT<TH1,TH2>", payloadCode, "@",
"RooUnfoldResponse", payloadCode, "@",
"RooUnfoldResponseT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldResponseT<TH1,TH2>", payloadCode, "@",
"RooUnfoldSpec", payloadCode, "@",
"RooUnfoldSvd", payloadCode, "@",
"RooUnfoldSvd::SVDUnfold", payloadCode, "@",
"RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldSvdT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>::SVDUnfold", payloadCode, "@",
"RooUnfoldSvdT<TH1,TH2>", payloadCode, "@",
"RooUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldT<TH1,TH2>", payloadCode, "@",
"RooUnfoldTUnfold", payloadCode, "@",
"RooUnfoldTUnfoldT<RooUnfolding::RooFitHist,RooUnfolding::RooFitHist>", payloadCode, "@",
"RooUnfoldTUnfoldT<TH1,TH2>", payloadCode, "@",
"RooUnfolding::RooFitHist", payloadCode, "@",
"TUnfoldBinningV17", payloadCode, "@",
"TUnfoldBinningXMLV17", payloadCode, "@",
"TUnfoldDensityV17", payloadCode, "@",
"TUnfoldIterativeEMV17", payloadCode, "@",
"TUnfoldSysV17", payloadCode, "@",
"TUnfoldV17", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libRooUnfold",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libRooUnfold_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libRooUnfold_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libRooUnfold() {
  TriggerDictionaryInitialization_libRooUnfold_Impl();
}
