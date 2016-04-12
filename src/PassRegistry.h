//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef _LIB_PASS_PASSREGISTRY_H_
#define _LIB_PASS_PASSREGISTRY_H_

#include "Type.h"

#include "PassInfo.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassRegistry  
	{
	private:
		static PassId2PassInfo& registeredPasses(void)
		{
			static PassId2PassInfo passes;
			return passes;
		}
	
	public:
		PassRegistry()
		{
			assert(0 && "PassRegistry class is a static-only non-object class!");
		}
		
		static void registerPass(PassInfo* passInfo)
		{
			assert( passInfo != 0 && "invalid pass info object pointer" );
			registeredPasses()[ passInfo->getPassId() ] = passInfo;
	
			// TODO: add checks for redundant argument names etc.
		}
		
		static PassId2PassInfo& getRegisteredPasses(void)
		{
			return registeredPasses();
		}
	
		static PassInfo& getPassInfo( PassId id )
		{
			PassInfo* pi  = static_cast< PassInfo* >( getRegisteredPasses()[ id ] );
		
			assert( pi != 0 && "invalid pass info object" );
		
			return *pi;
		}
	};

	template<class PassName>
	Pass* defaultConstructor()
	{
		return new PassName();
	}

	template<class PassName>
	class PassRegistration : public PassInfo
	{
	public:
		PassRegistration(const char* passName,
						 const char* passDescription,
						 const char* passArgStr,
						 const char  passArgChar
			)
			: PassInfo( passName,
						passDescription,
						passArgStr,
						passArgChar,
						&PassName::id,
						PassConstructor( defaultConstructor<PassName>) ) 
		{
			PassRegistry::registerPass(this);
		}
	};
}

#endif /* _LIB_PASS_PASSREGISTRY_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
