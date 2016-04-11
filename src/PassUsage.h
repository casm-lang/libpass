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

#ifndef _LIB_PASS_PASSUSAGE_H_
#define _LIB_PASS_PASSUSAGE_H_

// #include ...

/**
   @brief    TODO
   
   TODO
*/

namespace libpass
{
	class PassUsage  
	{
	private:
		// Type::PassIdSet dependsOnSet;
		// Type::PassIdSet invokesLaterSet;
		// Type::PassIdSet scheduleBeforeSet;
		// Type::PassIdSet scheduleAfterSet;
		
	public:
		
		/**
		   @brief    TODO
		   
		   TODO
		   
		   @param    arg0    TODO
		   @return   TODO
		   @retval   TODO
		*/
		
		template<class PassName>
		void dependsOn(void)
		{
			// dependsOnSet.insert( &PassName::id );
		}
		
		// const Type::PassIdSet& getDependsOn(void) const 
		// { 
		// 	return dependsOnSet; 
		// }
	
	
		template<class PassName>
		void invokesLater(void)
		{
			// invokesLaterSet.insert( &PassName::id );
		}

		// const Type::PassIdSet& getInvokesLater(void) const 
		// { 
		// 	return invokesLaterSet; 
		// }
	
	
		template<class PassName>
		void scheduleBefore(void)
		{
			// scheduleBeforeSet.insert( &PassName::id );
		}

		// const Type::PassIdSet& getScheduleBefore(void) const 
		// { 
		// 	return scheduleBeforeSet; 
		// }
	
	
		template<class PassName>
		void scheduleAfter(void)
		{
			// scheduleAfterSet.insert( &PassName::id );
		}

		// const Type::PassIdSet& getScheduleAfter(void) const 
		// { 
		// 	return scheduleAfterSet; 
		// }
	};
}

#endif /* _LIB_PASS_PASSUSAGE_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
