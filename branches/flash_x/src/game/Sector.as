package game 
{
	import core.Global;
	import editor.EditAction;
	import editor.UndoRedoController;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Sector extends GameNode
	{
		
		public static const k_SECTOR_UP:String = "SECTOR_UP";
		public static const k_SECTOR_MIDDLE:String = "SECTOR_MIDDLE";
		public static const k_SECTOR_DOWN:String = "SECTOR_DOWN";
		public static const k_SECTOR_DEFAULT_NAME:String = "sector_00";
		public static const k_SECTOR_NAME:String = "sector_0";
		
		public static const k_SECTOR_WIDTH:Number = 90;
		public static const k_SECTOR_HEIGHT:Number = 45;
		
		protected var m_bitmapList:Dictionary = new Dictionary();
		protected var m_sectorInQueue:String = "";
		
		protected var m_sectorName:String = "sector_00";
		
		protected var m_index:Point = new Point();
		
		protected var m_boundBitmapData:BitmapData = null;
		
		public function Sector(_container:DisplayObjectContainer) 
		{
			super(_container);
			
			m_bitmapList[k_SECTOR_UP] = new Bitmap();
			m_bitmapList[k_SECTOR_MIDDLE] = new Bitmap();
			m_bitmapList[k_SECTOR_DOWN] = new Bitmap();
			
			this.addChild(m_bitmapList[k_SECTOR_DOWN]);
			this.addChild(m_bitmapList[k_SECTOR_MIDDLE]);
			this.addChild(m_bitmapList[k_SECTOR_UP]);
		}
		
		override public function Load(_name:String, _sectorType:String):void 
		{
			m_sectorName = _name;
			m_sectorInQueue = _sectorType;
			super.Load(_name, _sectorType);
			super.LoadBoundData(k_SECTOR_DEFAULT_NAME);
		}
		
		override protected function onLoadResource(_data:BitmapData):void 
		{
			switch( m_sectorInQueue )
			{
				case k_SECTOR_UP :
				{
					(m_bitmapList[k_SECTOR_UP] as Bitmap).bitmapData = _data;
				}
				break;
				case k_SECTOR_MIDDLE :
				{
					(m_bitmapList[k_SECTOR_MIDDLE] as Bitmap).bitmapData = _data;
				}
				break;
				case k_SECTOR_DOWN :
				{
					(m_bitmapList[k_SECTOR_DOWN] as Bitmap).bitmapData = _data;
				}
				break;
				
				default :
				{
					//m_sectorInQueue = "";
					throw Error;
				}
			}
			//m_sectorInQueue = "";
		}
		
		override protected function onLoadBoundData(_data:BitmapData):void 
		{
			m_boundBitmapData = _data;
		}
		
		override protected function onUpdate(_event:Event):void 
		{
			m_intersect = isIntersect( Global.stage.mouseX, Global.stage.mouseY );
			super.onUpdate(_event);
		}
		
		override protected function onMouseClick(_event:MouseEvent):void 
		{
			m_intersect = isIntersect( _event.stageX, _event.stageY );
			if ( m_intersect )
			{
				if ( (k_SECTOR_NAME + Global.editorController.selectSectorName) == k_SECTOR_DEFAULT_NAME )
				{
					UndoRedoController.logAction(EditAction.k_REMOVE_ACTION, m_index, k_SECTOR_MIDDLE, m_sectorName, "");
					Global.editorController.removeSector(m_index);
					return;
				}
				
				if (m_sectorName == k_SECTOR_DEFAULT_NAME) 
				{
					UndoRedoController.logAction(EditAction.k_ADD_ACTION, m_index, k_SECTOR_MIDDLE, k_SECTOR_NAME + Global.editorController.selectSectorName, "");
					Global.editorController.addSector( m_index, k_SECTOR_NAME + Global.editorController.selectSectorName, k_SECTOR_MIDDLE );
				}
				else
				{
					UndoRedoController.logAction(EditAction.k_CHANGE_ACTION, m_index, k_SECTOR_MIDDLE, k_SECTOR_NAME + Global.editorController.selectSectorName, m_sectorName);
					Global.editorController.changeSector( m_index, k_SECTOR_NAME + Global.editorController.selectSectorName, k_SECTOR_MIDDLE );
				}
			}
		}
		
		protected function isIntersect(_x:Number, _y:Number):uint
		{
			if (m_boundBitmapData != null)
			{
				var mouseLocalPosition:Point = globalToLocal(new Point( _x, _y ));
				return m_boundBitmapData.getPixel(mouseLocalPosition.x, mouseLocalPosition.y);
			}
			else
			{
				return 0x00000000;
			}
		}
		
		public function unLoad(_sectorType:String):void
		{
			switch(_sectorType)
			{
				case k_SECTOR_DOWN :
				{
					(m_bitmapList[k_SECTOR_DOWN] as Bitmap).bitmapData = null;
				}
				break;
				
				case k_SECTOR_MIDDLE :
				{
					(m_bitmapList[k_SECTOR_DOWN] as Bitmap).bitmapData = null;
					(m_bitmapList[k_SECTOR_UP] as Bitmap).bitmapData = null;
					(m_bitmapList[k_SECTOR_MIDDLE] as Bitmap).bitmapData = null;
				}
				break;
				
				case k_SECTOR_UP :
				{
					(m_bitmapList[k_SECTOR_UP] as Bitmap).bitmapData = null;
				}
				break;
			}
		}
		
		public function set index(_value:Point):void
		{
			m_index = _value;
		}
		
		public function get index():Point
		{
			return m_index;
		}
		
		public function get sectorName():String 
		{
			return m_sectorName;
		}
		
		public function set sectorName(_value:String):void
		{
			m_sectorName = _value;
		}
	}

}