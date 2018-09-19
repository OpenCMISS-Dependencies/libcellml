#include <exception>
#include "cda_compiler_support.h"
#include <map>
#include <string>
#include "CellMLContextBootstrap.hxx"
#include "Utilities.hxx"
#include "IfaceDOM_events.hxx"

class CDA_ModuleManager;

class CDA_CellMLModuleIterator
  : public iface::cellml_context::CellMLModuleIterator
{
public:
  CDA_CellMLModuleIterator(CDA_ModuleManager* aMM,
                           std::list<iface::cellml_context::CellMLModule*>&
                           aList);
  ~CDA_CellMLModuleIterator();

  CDA_IMPL_REFCOUNT;
  CDA_IMPL_ID;
  CDA_IMPL_QI1(cellml_context::CellMLModuleIterator)

  already_AddRefd<iface::cellml_context::CellMLModule> nextModule()
    throw(std::exception&);

  void invalidate(std::list<iface::cellml_context::CellMLModule*>::iterator&
                  aInv) { if (aInv == mCurrent) mCurrent++; };
private:
  CDA_ModuleManager* mMM;
  std::list<iface::cellml_context::CellMLModule*>& mList;
  std::list<iface::cellml_context::CellMLModule*>::iterator
    mCurrent;
  std::list<CDA_CellMLModuleIterator*>::iterator mItIt;
};

class CDA_ModelNode;
class CDA_ModelList;

class CDA_ModelNodeIterator
  : public iface::cellml_context::ModelNodeIterator
{
public:
  CDA_ModelNodeIterator(CDA_ModelList* aML,
                        std::list<CDA_ModelNode*>&
                        aList);
  ~CDA_ModelNodeIterator();

  CDA_IMPL_REFCOUNT;
  CDA_IMPL_ID;
  CDA_IMPL_QI1(cellml_context::ModelNodeIterator)

  already_AddRefd<iface::cellml_context::ModelNode> nextModelNode()
    throw(std::exception&);

  void invalidate(std::list<CDA_ModelNode*>::iterator&
                  aInv) { if (aInv == mCurrent) mCurrent++; };
private:
  CDA_ModelList* mML;
  std::list<CDA_ModelNode*>& mList;
  std::list<CDA_ModelNode*>::iterator
    mCurrent;
  std::list<CDA_ModelNodeIterator*>::iterator mItIt;
};

class CDA_TypeAnnotationManager
  : public iface::cellml_context::CellMLTypeAnnotationManager
{
public:
  CDA_TypeAnnotationManager() {}
  ~CDA_TypeAnnotationManager();

  CDA_IMPL_REFCOUNT;
  CDA_IMPL_ID;
  CDA_IMPL_QI1(cellml_context::CellMLTypeAnnotationManager);

  void setUserData(const std::wstring& type, const std::wstring& key,
                   iface::XPCOM::IObject* data)
    throw(std::exception&);
  already_AddRefd<iface::XPCOM::IObject> getUserData(const std::wstring& type, const std::wstring& key)
    throw(std::exception&);

private:
  std::map<std::pair<std::wstring,std::wstring>, iface::XPCOM::IObject*>
    annotations;
};

class CDA_ModuleManager
  : public iface::cellml_context::CellMLModuleManager
{
public:
  CDA_ModuleManager();
  ~CDA_ModuleManager();

  CDA_IMPL_REFCOUNT;
  CDA_IMPL_ID;
  CDA_IMPL_QI1(cellml_context::CellMLModuleManager);

  void registerModule(iface::cellml_context::CellMLModule* aModule)
    throw(std::exception&);
  void deregisterModule(iface::cellml_context::CellMLModule* aModule)
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::CellMLModule> findModuleByName
  (const std::wstring& moduleName, const std::wstring& moduleVersion)
    throw(std::exception&);
  void requestModuleByName(const std::wstring& moduleName,
                           const std::wstring& moduleVersion)
    throw(std::exception&);
  void addMonitor(iface::cellml_context::CellMLModuleMonitor* aModuleMonitor)
    throw(std::exception&);
  void removeMonitor(iface::cellml_context::CellMLModuleMonitor*
                     aModuleMonitor)
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::CellMLModuleIterator> iterateModules()
    throw(std::exception&);

  std::list<CDA_CellMLModuleIterator*>::iterator registerIterator(CDA_CellMLModuleIterator* aIt)
    { mIterators.push_back(aIt); return --mIterators.end(); };
  void deregisterIterator(std::list<CDA_CellMLModuleIterator*>::iterator& aItIt)
    { mIterators.erase(aItIt); };

private:
  std::map<std::pair<std::wstring,std::wstring>,
           iface::cellml_context::CellMLModule*> mRegisteredModules;
  std::list<iface::cellml_context::CellMLModule*> mRegisteredModuleList;
  std::list<iface::cellml_context::CellMLModuleMonitor*> mMonitors;
  std::list<CDA_CellMLModuleIterator*> mIterators;
};

class CDA_ModelList;

class CDA_ModelNode
  : public iface::cellml_context::ModelNode,
    public iface::events::EventListener
{
public:
  CDA_ModelNode(iface::cellml_api::Model* aModel);
  ~CDA_ModelNode();
  
  void add_ref() throw();
  void release_ref() throw();

  CDA_IMPL_QI1(cellml_context::ModelNode);
  CDA_IMPL_ID;

  void name(const std::wstring& name) throw(std::exception&);
  std::wstring name() throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelNode> getLatestDerivative()
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelNode> getWritable() throw(std::exception&);
  bool isFrozen() throw(std::exception&);
  void isFrozen(bool) throw(std::exception&);
  uint32_t modificationTimestamp() throw(std::exception&);
  void stampModifiedNow() throw(std::exception&);
  already_AddRefd<iface::cellml_api::Model> model() throw(std::exception&);
  void model(iface::cellml_api::Model* aModel) throw (std::exception&);
  void flushChanges() throw(std::exception&);
  already_AddRefd<iface::XPCOM::IObject> owner() throw(std::exception&);
  void owner(iface::XPCOM::IObject* aOwner) throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelList> derivedModels() throw(std::exception&);
  void addModelMonitor(iface::cellml_context::ModelNodeMonitor* monitor)
    throw(std::exception&);
  void removeModelMonitor(iface::cellml_context::ModelNodeMonitor* monitor)
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelList> parentList()
    throw(std::exception&);

  void setParentList(CDA_ModelList* aParentList);
  void dirty(bool aDirty) throw(std::exception&);
  bool dirty() throw(std::exception&);

  void handleEvent(iface::events::Event* aEvent) throw(std::exception&);

private:
  std::wstring mName;
  uint32_t mTimestamp;
  iface::cellml_api::Model* mModel;
  ObjRef<iface::XPCOM::IObject> mOwner;
  CDA_ModelList* mDerivedModels;
  bool mIsFrozen;
  std::list<iface::cellml_context::ModelNodeMonitor*> mModelMonitors;
  CDA_RefCount _cda_refcount;
  bool mModelDirty;

  void installModelEventListener(iface::cellml_api::Model* aModel);
  void removeModelEventListener(iface::cellml_api::Model* aModel);

public: // within CellMLContextImplementation only...
  // Not refcounted, but set/cleared automatically when added/removed.
  CDA_ModelList* mParentList;
};

class CDA_ModelList
  : public iface::cellml_context::ModelList
{
public:
  CDA_ModelList();
  ~CDA_ModelList();

  void add_ref() throw();
  void release_ref() throw();
  CDA_IMPL_QI1(cellml_context::ModelList);
  CDA_IMPL_ID;

  void addModelMonitor(iface::cellml_context::ModelNodeMonitor* monitor)
    throw(std::exception&);
  void removeModelMonitor(iface::cellml_context::ModelNodeMonitor* monitor)
    throw(std::exception&);
  void addListMonitor(iface::cellml_context::ModelListMonitor* monitor)
    throw(std::exception&);
  void removeListMonitor(iface::cellml_context::ModelListMonitor* monitor)
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelNode> makeNode(iface::cellml_api::Model* mod)
    throw(std::exception&);
  void addModel(iface::cellml_context::ModelNode* node)
    throw(std::exception&);
  void removeModel(iface::cellml_context::ModelNode* node)
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelNodeIterator> iterateModelNodes()
    throw(std::exception&);
  already_AddRefd<iface::cellml_context::ModelNode> parentNode()
    throw(std::exception&);
  std::list<CDA_ModelNodeIterator*>::iterator registerIterator(CDA_ModelNodeIterator* aIt)
    { mIterators.push_back(aIt); return --mIterators.end(); }
  void deregisterIterator(std::list<CDA_ModelNodeIterator*>::iterator& aItIt)
    { mIterators.erase(aItIt); }

private:
  std::list<CDA_ModelNode*> mModels;
  std::list<CDA_ModelNodeIterator*> mIterators;
public: // within CellMLContextImplementation only...
  // Not refcounted, but set/cleared automatically when added/removed.
  CDA_ModelNode* mParentNode;
  std::list<iface::cellml_context::ModelNodeMonitor*> mNodeMonitors;
  std::list<iface::cellml_context::ModelListMonitor*> mListMonitors;

private:
  CDA_RefCount _cda_refcount;
};

class CDA_CellMLContext
  : public iface::cellml_context::CellMLContext
{
public:
  CDA_CellMLContext();
  ~CDA_CellMLContext();

  CDA_IMPL_REFCOUNT;
  CDA_IMPL_QI1(cellml_context::CellMLContext);
  CDA_IMPL_ID;

  already_AddRefd<iface::cellml_context::CellMLModuleManager>
  moduleManager()
    throw(std::exception&)
  {
    mModuleManager->add_ref();
    return mModuleManager;
  }

  already_AddRefd<iface::cellml_context::CellMLTypeAnnotationManager>
  typeAnnotationManager()
    throw(std::exception&)
  {
    mTypeAnnotationManager->add_ref();
    return mTypeAnnotationManager;
  }

  already_AddRefd<iface::cellml_api::CellMLBootstrap>
  cellmlBootstrap()
    throw(std::exception&)
  {
    mCellMLBootstrap->add_ref();
    return mCellMLBootstrap;
  }

  already_AddRefd<iface::cellml_context::ModelList>
  loadedModels()
    throw(std::exception&)
  {
    mModelList->add_ref();
    return mModelList;
  }

private:
  iface::cellml_context::CellMLModuleManager* mModuleManager;
  iface::cellml_context::CellMLTypeAnnotationManager* mTypeAnnotationManager;
  iface::cellml_api::CellMLBootstrap* mCellMLBootstrap;
  iface::cellml_context::ModelList* mModelList;
};
