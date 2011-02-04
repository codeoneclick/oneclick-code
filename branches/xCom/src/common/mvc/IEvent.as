package common.mvc 
{
	import flash.events.Event;
	/**
	 * ...
	 * @author ...
	 */
	public class IEvent extends Event
	{
		private var m_data:*;
		public function IEvent(_event:String,_data:*) 
		{
			m_data = _data;
			super(_event, false, false);
		}
		
		public function get data():*
		{
			return m_data;
		}
		
	}

}