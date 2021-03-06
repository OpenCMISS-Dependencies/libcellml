/* This file is automatically generated from CeLEDS.idl
 * DO NOT EDIT DIRECTLY OR CHANGES WILL BE LOST!
 */
#ifndef _GUARD_IFACE_CeLEDS
#define _GUARD_IFACE_CeLEDS
#include "cda_compiler_support.h"
#ifdef MODULE_CONTAINS_CeLEDS
#define PUBLIC_CeLEDS_PRE CDA_EXPORT_PRE
#define PUBLIC_CeLEDS_POST CDA_EXPORT_POST
#else
#define PUBLIC_CeLEDS_PRE CDA_IMPORT_PRE
#define PUBLIC_CeLEDS_POST CDA_IMPORT_POST
#endif
#include "Ifacexpcom.hxx"
#include "IfaceDOM_APISPEC.hxx"
#include "IfaceMathML_content_APISPEC.hxx"
#include "IfaceCellML_APISPEC.hxx"
#include "IfaceCUSES.hxx"
#include "IfaceAnnoTools.hxx"
#include "IfaceCeVAS.hxx"
#include "IfaceMaLaES.hxx"
namespace iface
{
  namespace cellml_services
  {
    PUBLIC_CeLEDS_PRE 
    class  PUBLIC_CeLEDS_POST LanguageDictionary
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::LanguageDictionary"; }
      virtual ~LanguageDictionary() {}
      virtual std::wstring getValue(const std::wstring& keyName) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::dom::NodeList>  getMappings() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_CeLEDS_PRE 
    class  PUBLIC_CeLEDS_POST DictionaryGenerator
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::DictionaryGenerator"; }
      virtual ~DictionaryGenerator() {}
      virtual already_AddRefd<iface::cellml_services::LanguageDictionary>  getDictionary(const std::wstring& dictionaryNameSpace) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::dom::Element>  getElementNS(const std::wstring& nameSpace, const std::wstring& elementName) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::cellml_services::MaLaESTransform>  getMalTransform() throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
    };
    PUBLIC_CeLEDS_PRE 
    class  PUBLIC_CeLEDS_POST CeLEDSBootstrap
     : public virtual iface::XPCOM::IObject
    {
    public:
      static const char* INTERFACE_NAME() { return "cellml_services::CeLEDSBootstrap"; }
      virtual ~CeLEDSBootstrap() {}
      virtual already_AddRefd<iface::cellml_services::DictionaryGenerator>  createDictGenerator(const std::wstring& URL) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual already_AddRefd<iface::cellml_services::DictionaryGenerator>  createDictGeneratorFromText(const std::wstring& XMLText) throw(std::exception&) WARN_IF_RETURN_UNUSED = 0;
      virtual std::wstring loadError() throw(std::exception&)  WARN_IF_RETURN_UNUSED = 0;
    };
  };
};
#undef PUBLIC_CeLEDS_PRE
#undef PUBLIC_CeLEDS_POST
#endif // guard
