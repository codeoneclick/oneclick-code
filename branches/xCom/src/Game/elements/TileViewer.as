package Game.elements 
{
	import common.mvc.IViewer;
	import flash.events.Event;
	/**
	 * ...
	 * @author ...
	 */
	public class TileViewer extends IViewer
	{
		
		public function TileViewer(_url:String, _dataType:String) 
		{
			super(_url, _dataType);
		}
		
		override protected function update(_event:Event):void
		{
			super.update(_event);
		}
		
	}

}