package common.mvc 
{
	import flash.events.Event;
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class IEvent extends Event
	{
		private var m_data:*;
		
		public function get Data():*
		{
			return m_data;
		}

		public function IEvent(_event:String,_data:*) 
		{
			m_data = _data;
			super(_event, false, false);
		}
		
	}

}