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

#ifndef _LIB_PASS_PASSINFO_H_
#define _LIB_PASS_PASSINFO_H_

#include "Type.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassInfo
	{
	private:
		const char* const name;
		const char* const description;
		const char* const arg_str;
		const char        arg_char;
	
		const PassId  id;
	
		PassConstructor constructor;
	
		uint64_t changes;

	public:
		PassInfo
		( const char* passName
		, const char* passDescription
		, const char* passArgStr
		, const char  passArgChar
		, const PassId passID
		, PassConstructor passConstructor
		)
		: name( passName )
		, description( passDescription )
		, arg_str( passArgStr )
		, arg_char( passArgChar )
		, id( passID )
		, constructor( passConstructor )
		{
		}
		
		const char* getPassName(void) const 
		{ 
			return name; 
		}
	
		const char* getPassDescription(void) const 
		{ 
			return description; 
		}
	
		const char* getPassArgString(void) const 
		{ 
			return arg_str; 
		}
	
		const char getPassArgChar(void) const 
		{ 
			return arg_char; 
		}
	
		const PassId getPassId(void) const
		{
			return id;
		}

		bool isPassID(const PassId passID) const
		{
			return passID == id;
		}
	
		void addChanges(uint64_t change)
		{
			changes += change;
		}
	
		uint64_t getChanges(void)
		{
			return changes;
		}
	
		Pass* constructPass(void) const
		{
			return constructor();
		}
	
		friend ostream& operator<<(ostream& os, PassInfo& pi)
		{
			return os; // << pi.getPassName() << ": ";
		}
	};
}

#endif /* _LIB_PASS_PASSINFO_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
