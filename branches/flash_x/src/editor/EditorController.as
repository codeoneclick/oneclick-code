package editor 
{
	import core.Global;
	import flash.geom.Point;
	import game.Sector;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class EditorController 
	{
		private var m_selectSectorName:int = 0;
		
		public function EditorController() 
		{
			
		}
		
		public function get selectSectorName():int
		{
			return m_selectSectorName;
		}
		
		public function set selectSectorName(_value:int):void
		{
			m_selectSectorName = _value;
		}
		
		public function addSector(_position:Point, _sectorName:String, _sectorType:String):void
		{
			Global.sceneController.addSector( _position, _sectorName, _sectorType );
			Global.sceneController.addSector( _position, "sector_down_10", Sector.k_SECTOR_DOWN );
			Global.sceneController.addSubSectors( _position );
			Global.sceneController.zOrder();
		}
		
		public function changeSector(_position:Point, _sectorName:String, _sectorType:String):void
		{
			Global.sceneController.changeSector(_position, _sectorName, _sectorType);
		}
		
		public function removeSector(_position:Point):void
		{
			Global.sceneController.removeSector(_position);
			Global.sceneController.removeSubSectors(_position);
			Global.sceneController.zOrder();
		}
		
	}

}