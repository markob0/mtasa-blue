/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/deathmatch/logic/CResourceFile.h
*  PURPOSE:     Resource server-side file item class
*  DEVELOPERS:  Ed Lyons <>
*               Jax <>
*               Chris McArthur <>
*               Christian Myhre Lundheim <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

// This class controls a single resource file. This could be
// any item contained within the resource, mainly being a
// map or script.

// This is just a base class.

class CResourceFile;

#ifndef CRESOURCEFILE_H
#define CRESOURCEFILE_H
#include "ehs/ehs.h"

class CResourceFile
{
public:
    enum eResourceType
    {
        RESOURCE_FILE_TYPE_MAP,
        RESOURCE_FILE_TYPE_SCRIPT,
        RESOURCE_FILE_TYPE_CLIENT_SCRIPT,
        RESOURCE_FILE_TYPE_CONFIG,
        RESOURCE_FILE_TYPE_CLIENT_CONFIG,
        RESOURCE_FILE_TYPE_HTML,
        RESOURCE_FILE_TYPE_CLIENT_FILE,
        RESOURCE_FILE_TYPE_NONE,
    }; // TODO: sort all client-side enums and use >= (instead of each individual type) on comparisons that use this enum?

protected:
    class CResource *           m_resource;
    std::string                 m_strResourceFileName;  // full path
    std::string                 m_strShortName;         // just the filename
    std::string                 m_strWindowsName;       // the name with backwards slashes
    eResourceType               m_type;
    class CLuaMain *            m_pVM;
    unsigned long               m_ulCRC; // CRC last time this was loaded, generated by GenerateCRC()
    map < string, string >      m_attributeMap; // Map of attributes from the meta.xml file
    
public:
                                CResourceFile ( class CResource * resource, const char* szShortName, const char* szResourceFileName, CXMLAttributes * xmlAttributes );
    virtual                     ~CResourceFile ( void );

    virtual ResponseCode        Request ( HttpRequest * ipoHttpRequest, HttpResponse * ipoHttpResponse );

    virtual bool                Start ( void ) = 0;
    virtual bool                Stop ( void ) = 0;

    inline eResourceType        GetType() { return m_type; }
    inline const char *         GetPath() { return m_strResourceFileName.c_str (); }
    inline const char *         GetName() { return m_strShortName.c_str (); }
    inline const char *         GetWindowsName() { return m_strWindowsName.c_str (); }

    inline unsigned long        GetLastCRC ( void ) { return m_ulCRC; }
    void                        SetLastCRC ( unsigned long ulCRC ) { m_ulCRC = ulCRC; }

    double                      GetSize ( void );
    string                      GetMetaFileAttribute ( const string& key ) { return m_attributeMap[key]; }
};

#endif
