package editor 
{
	import core.Global;
	import flash.geom.Point;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class UndoRedoController 
	{
		private static var m_logActionQueue:Vector.<EditAction> = new Vector.<EditAction>();
		private static var m_unlogActionQueue:Vector.<EditAction> = new Vector.<EditAction>();
		
		public function UndoRedoController() 
		{
			
		}
		
		public static function logAction(_action:String, _position:Point, _sectorType:String, _sectorName:String, _oldSectorName:String):void
		{
			var action:EditAction = new EditAction();
			action.action = _action;
			action.position = _position;
			action.sectorName = _sectorName;
			action.sectorType = _sectorType;
			action.oldSectorName = _oldSectorName;
			m_logActionQueue.push(action);
		}
		
		public static function unlogAction():void
		{
			
		}
		
		public static function undo():void
		{
			if (m_logActionQueue.length > 0)
			{
				var action:EditAction = m_logActionQueue.pop();
				switch(action.action)
				{
					case EditAction.k_ADD_ACTION :
					{
						Global.editorController.removeSector(action.position);
					}
					break;
					case EditAction.k_REMOVE_ACTION :
					{
						Global.editorController.addSector(action.position,action.sectorName,action.sectorType);
					}
					break;
					case EditAction.k_CHANGE_ACTION :
					{
						Global.editorController.changeSector(action.position,action.oldSectorName,action.sectorType);
					}
					break;
				}
				m_unlogActionQueue.push(action);
			}
		}
		
		public static function redo():void
		{
			
		}
		
	}

}