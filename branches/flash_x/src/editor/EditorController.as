package editor 
{
	import core.Global;
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class EditorController 
	{
		private var m_previewSelectedIndex:int = 0;
		
		public function EditorController() 
		{
			
		}
		
		public function get previewSelectedIndex():int
		{
			return m_previewSelectedIndex;
		}
		
		public function set previewSelectedIndex(_value:int):void
		{
			m_previewSelectedIndex = _value;
		}
		
		public function addSector(_position:Point, _sectorName:String, _sectorType:String):void
		{
			Global.sceneController.addSector( _position, _sectorName, _sectorType );
			Global.sceneController.addSubSectors( _position );
			Global.sceneController.zOrder();
		}
		
		public function changeSector(_position:Point, _sectorName:String, _sectorType:String):void
		{
			Global.sceneController.changeSector(_position, _sectorName, _sectorType);
		}
		
		public function removeSector():void
		{
			
		}
		
	}

}