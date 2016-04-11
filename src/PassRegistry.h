//  
//  Copyright (c) 2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
//  
//  This software is licensed under the Open Software License v. 3.0 (OSL-3.0).
//  You either find the license text below or in the root directory of this 
//  project in the LICENSE.txt file. If you cannot find the LICENSE.txt file,
//  please refer to https://opensource.org/licenses/OSL-3.0.
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
