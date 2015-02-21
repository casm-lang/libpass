
/*
  Copyright (C) 2015 Philipp Paulweber
  
  This file is part of the 'libpass' project which is released under a NSCA
  open source software license. For more information, see the LICENSE.txt
  file in the project root directory.
*/

#ifndef _LIB_PASS_PASSUSAGE_H_
#define _LIB_PASS_PASSUSAGE_H_

// #include ...

/**
   @file     PassUsage.h
   @class    PassUsage
   
   @brief    TODO
   
   TODO
   
   @author   Philipp Paulweber
   @date     2015-02-14
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


/*
  Local variables:
  mode: c++
  indent-tabs-mode: t
  c-basic-offset: 4
  tab-width: 4
  End:
  vim:noexpandtab:sw=4:ts=4:
*/
