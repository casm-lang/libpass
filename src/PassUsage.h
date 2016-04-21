//  
//  Copyright (c) 2015-2016 Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Philipp Paulweber
//                https://github.com/ppaulweber/libpass
//  
//  This file is part of libpass.
//  
//  libpass is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  libpass is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with libpass. If not, see <http://www.gnu.org/licenses/>.
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
