//  
//  Copyright (c) 2015 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
//  
//  Permission is hereby granted, free of charge, to any person obtaining a 
//  copy of this software and associated documentation files (the "Software"), 
//  to deal with the Software without restriction, including without limitation 
//  the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//  and/or sell copies of the Software, and to permit persons to whom the 
//  Software is furnished to do so, subject to the following conditions:
//  
//  * Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimers.
//  
//  * Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimers in the 
//    documentation and/or other materials provided with the distribution.
//  
//  * Neither the names of the copyright holders, nor the names of its 
//    contributors may be used to endorse or promote products derived from 
//    this Software without specific prior written permission.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
//  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
//  WITH THE SOFTWARE.
//  

#ifndef _LIB_PASS_PASSREGISTRY_H_
#define _LIB_PASS_PASSREGISTRY_H_

#include "Type.h"

#include "PassInfo.h"

/**
   @file     PassRegistry.h
   @class    PassRegistry
   
   @brief    TODO
   
   TODO
   
   @author   Philipp Paulweber
   @date     2015-02-14
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
	
		/**
		   @brief    TODO

		   TODO
	   
		   @param    arg0    TODO
		   @return   TODO
		   @retval   TODO
		*/
	
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
