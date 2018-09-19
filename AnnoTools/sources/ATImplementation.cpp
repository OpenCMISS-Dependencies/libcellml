#define IN_ANNOTOOLS_MODULE
#define MODULE_CONTAINS_AnnoTools
#include "ATImplementation.hpp"
#include "AnnoToolsBootstrap.hpp"

CDAStringAnnotationImpl::CDAStringAnnotationImpl(const std::wstring& aValue)
  throw()
  : mString(aValue)
{
}

void
CDAStringAnnotationImpl::value(const std::wstring& aValue)
  throw(std::exception&)
{
  mString = aValue;
}

std::wstring
CDAStringAnnotationImpl::value()
  throw(std::exception&)
{
  return mString;
}

CDAObjectAnnotationImpl::CDAObjectAnnotationImpl(iface::XPCOM::IObject* aValue)
  throw()
  : mObject(aValue)
{
}

void
CDAObjectAnnotationImpl::value(iface::XPCOM::IObject* aValue)
  throw(std::exception&)
{
  mObject = aValue;
}

already_AddRefd<iface::XPCOM::IObject>
CDAObjectAnnotationImpl::value()
  throw(std::exception&)
{
  mObject->add_ref();
  return mObject.getPointer();
}

CDAAnnotationSetImpl::CDAAnnotationSetImpl()
  throw()
{
  mPrefixURI = L"http://www.cellml.org/tools/annotools/set";
  size_t i;
#define CHARS L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_."
  for (i = 0; i < 10; i++)
  {
    unsigned long r = sharedRandom()->randomUInt32();
    mPrefixURI += CHARS[r & 0x3F];
    r >>= 6;
    mPrefixURI += CHARS[r & 0x3F];
    r >>= 6;
    mPrefixURI += CHARS[r & 0x3F];
    r >>= 6;
    mPrefixURI += CHARS[r & 0x3F];
    r >>= 6;
    mPrefixURI += CHARS[r & 0x3F];
  }
#undef CHARS

  mPrefixURI += L"/";
}

CDAAnnotationSetImpl::~CDAAnnotationSetImpl()
  throw()
{
  std::list<std::pair<std::wstring, iface::cellml_api::CellMLElement*> >::iterator
    i = mAnnotations.begin();
  for (; i != mAnnotations.end(); i++)
  {
    std::wstring key = mPrefixURI + (*i).first;
    (*i).second->setUserData(key.c_str(), NULL);
    (*i).second->release_ref();
  }
}

std::wstring
CDAAnnotationSetImpl::prefixURI()
  throw(std::exception&)
{
  return mPrefixURI;
}

std::wstring
CDAAnnotationSetImpl::getStringAnnotation
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;

  RETURN_INTO_OBJREF(ud, iface::cellml_api::UserData,
                     aElement->getUserDataWithDefault(key.c_str(), NULL));
  DECLARE_QUERY_INTERFACE_OBJREF(sa, ud, cellml_services::StringAnnotation);
    
  if (sa == NULL)
    return L"";
    
    return sa->value();
}

std::wstring
CDAAnnotationSetImpl::getStringAnnotationWithDefault
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey,
 const std::wstring& aDefault
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;

  RETURN_INTO_OBJREF(ud, iface::cellml_api::UserData,
                     aElement->getUserDataWithDefault(key.c_str(), NULL));
  DECLARE_QUERY_INTERFACE_OBJREF(sa, ud, cellml_services::StringAnnotation);
    
  if (sa == NULL)
    return aDefault;
    
  return sa->value();
}


void
CDAAnnotationSetImpl::setStringAnnotation
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey,
 const std::wstring& aValue
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;
  
  aElement->add_ref();
  mAnnotations.push_back(std::pair<std::wstring,
                         iface::cellml_api::CellMLElement*>(aKey, aElement));

  RETURN_INTO_OBJREF(anno, iface::cellml_services::StringAnnotation,
                     new CDAStringAnnotationImpl(aValue));
  aElement->setUserData(key.c_str(), anno);
}

already_AddRefd<iface::XPCOM::IObject>
CDAAnnotationSetImpl::getObjectAnnotation
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;

  RETURN_INTO_OBJREF(ud, iface::cellml_api::UserData,
                     aElement->getUserDataWithDefault(key.c_str(), NULL));
  DECLARE_QUERY_INTERFACE_OBJREF(oa, ud, cellml_services::ObjectAnnotation);
    
  if (oa == NULL)
    return NULL;
    
  return oa->value();
}

already_AddRefd<iface::XPCOM::IObject>
CDAAnnotationSetImpl::getObjectAnnotationWithDefault
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey,
 iface::XPCOM::IObject* aDefault
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;

  RETURN_INTO_OBJREF(ud, iface::cellml_api::UserData,
                     aElement->getUserDataWithDefault(key.c_str(), NULL));
  DECLARE_QUERY_INTERFACE_OBJREF(oa, ud, cellml_services::ObjectAnnotation);

  if (oa == NULL)
  {
    if (aDefault != NULL)
      aDefault->add_ref();
    return aDefault;
  }

  return oa->value();
}

void
CDAAnnotationSetImpl::setObjectAnnotation
(
 iface::cellml_api::CellMLElement* aElement,
 const std::wstring& aKey,
 iface::XPCOM::IObject* aValue
)
  throw(std::exception&)
{
  std::wstring key = mPrefixURI;
  key += aKey;
  
  if (aValue == NULL)
  {
    // Just clear the key. No point cleaning up mAnnotations, because this
    // object is supposed to be fairly short lived anyway.
    aElement->setUserData(key.c_str(), NULL);
    return;
  }

  aElement->add_ref();
  mAnnotations.push_back(std::pair<std::wstring,
                         iface::cellml_api::CellMLElement*>(aKey, aElement));

  RETURN_INTO_OBJREF(anno, iface::cellml_services::ObjectAnnotation,
                     new CDAObjectAnnotationImpl(aValue));
  aElement->setUserData(key.c_str(), anno);
}

already_AddRefd<iface::cellml_services::AnnotationToolService>
CreateAnnotationToolService(void)
{
  return new CDAAnnotationToolServiceImpl();
}
