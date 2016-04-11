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

#ifndef _LIB_PASS_PASSRESULT_H_
#define _LIB_PASS_PASSRESULT_H_

#include "Type.h"

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassResult  
	{
	private:
	
		PassId2Ptr results;
	
		PassId2u64 changes;
	
	public:
		PassResult()
		{
		}
	
		~PassResult()
		{
			results.clear();
			changes.clear();
		}
	
		template<class PassName>
		void* getResult(void)
		{
			return results[ &PassName::id ];
		}
	
		template<class PassName>
		void setResult(void* passResult)
		{
			results[ &PassName::id ] = passResult;
		}
	
		PassId2Ptr& getResults(void)
		{
			return results;
		}
	
		void printAllResults(void)
		{
		}
	
		uint64_t getChanges(PassId id)
		{
			return changes[ id ];
		}
	
		template<class PassName>
		void setChanges(uint64_t passChanges)
		{
			changes[ &PassName::id ] = passChanges;
		
			if( passChanges > 0 )
			{
			} 
		}
	
		void setChanges(PassId id, uint64_t passChanges)
		{
			changes[ id ] = passChanges;
		}
	
		friend ostream& operator<<(ostream& os, PassResult& pr)
		{
			return os;
		}	
	};
}

#endif /* _LIB_PASS_PASSRESULT_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
