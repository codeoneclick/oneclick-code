package Game.elements 
{
	import common.mvc.IEvent;
	/**
	 * ...
	 * @author ...
	 */
	public class TileEvent extends IEvent
	{
		public static var k_UPDATE_POSITION:String = "update_position";
		public static var k_MOUSE_OVER:String = "mouse_over";
		public static var k_MOUSE_OUT:String = "mouse_out";
		
		public function TileEvent(_event:String,_data:*) 
		{
			super(_event, _data);
		}
		
	}

}