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
		
		private static var m_undoQueue:Vector.<Object> = new Vector.<Object>();
		private static var m_redoQueue:Vector.<Object> = new Vector.<Object>();
		
		public static const k_SECTOR_EDIT_MODE:int = 1;
		public static const k_DECO_EDIT_MODE:int = 2;
		
		public static const k_EDIT_ADD:String = "EDIT_ADD";
		public static const k_EDIT_CHANGE:String = "EDIT_CHANGE";
		public static const k_EDIT_REMOVE:String = "EDIT_REMOVE";
		
		private var m_pickBookmarkName:int = 0;
		private var m_pickSectorName:int = 0;
		private var m_pickDecoName:int = 0;
		
		public function EditorController() 
		{
			
		}
		
		public function get pickSectorName():int
		{
			return m_pickSectorName;
		}
		
		public function set pickSectorName(_value:int):void
		{
			m_pickSectorName = _value;
		}
		
		public function get pickDecoName():int
		{
			return m_pickDecoName;
		}
		
		public function set pickDecoName(_value:int):void
		{
			m_pickDecoName = _value;
		}
		
		public function get pickBookmarkName():int
		{
			return m_pickBookmarkName;
		}
		
		public function set pickBookmarkName(_value:int):void
		{
			m_pickBookmarkName = _value;
		}
		
		public function addSector(_position:Point, _name:String, _layer:int):void
		{
			Global.sceneController.addSector( _position, _name, _layer );
			if (_layer == Sector.k_SECTOR_LAYER)
			{
				Global.sceneController.addSubSectors( _position );
			}
			Global.sceneController.zOrder();
		}
		
		public function changeSector(_position:Point, _name:String, _layer:int):void
		{
			Global.sceneController.changeSector(_position, _name, _layer);
		}
		
		public function removeSector(_position:Point, _layer:int):void
		{
			Global.sceneController.removeSector(_position, _layer);
			if (_layer == Sector.k_SECTOR_LAYER)
			{
				Global.sceneController.removeSubSectors(_position);
			}
			Global.sceneController.zOrder();
		}
		
		public function addLog(_action:String, _position:Point, _layer:int, _name:String, _oldName:String):void
		{
			var action:Object = new Object();
			action.action = _action;
			action.position = _position;
			action.sectorName = _name;
			action.sectorType = _layer;
			action.oldSectorName = _oldName;
			m_undoQueue.push(action);
			m_redoQueue = new Vector.<Object>();
		}
		
		public function removeLog():void
		{
			
		}
		
		public function undo():void
		{
			if (m_undoQueue.length > 0)
			{
				var action:Object = m_undoQueue.pop();
				switch(action.action)
				{
					case k_EDIT_ADD :
					{
						removeSector(action.position, action.sectorType);
					}
					break;
					case k_EDIT_REMOVE :
					{
						addSector(action.position,action.sectorName,action.sectorType);
					}
					break;
					case k_EDIT_CHANGE :
					{
						changeSector(action.position,action.oldSectorName,action.sectorType);
					}
					break;
				}
				m_redoQueue.push(action);
			}
		}
		
		public function redo():void
		{
			
		}
		
	}

}