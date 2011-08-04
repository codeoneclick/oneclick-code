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
		
		public static const k_EDIT_ADD:String = "EDIT_ADD";
		public static const k_EDIT_CHANGE:String = "EDIT_CHANGE";
		public static const k_EDIT_REMOVE:String = "EDIT_REMOVE";
		
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
		
		public function addLog(_action:String, _position:Point, _sectorType:String, _sectorName:String, _oldSectorName:String):void
		{
			var action:Object = new Object();
			action.action = _action;
			action.position = _position;
			action.sectorName = _sectorName;
			action.sectorType = _sectorType;
			action.oldSectorName = _oldSectorName;
			m_undoQueue.push(action);
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
						removeSector(action.position);
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