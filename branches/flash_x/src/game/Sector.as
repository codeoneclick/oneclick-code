package game 
{
	import core.Global;
	import editor.EditorController;
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
		
		public static const k_SECTOR_LAYER_01:String = "SECTOR_LAYER_01";
		public static const k_SECTOR_LAYER_02:String = "SECTOR_LAYER_02";
		public static const k_SECTOR_DEFAULT_NAME:String = "sector_00";
		public static const k_SECTOR_NAME:String = "sector_0";
		public static const k_DECO_DEFAULT_NAME:String = "deco_00";
		public static const k_DECO_NAME:String = "deco_0";
		
		public static const k_SECTOR_WIDTH:Number = 90;
		public static const k_SECTOR_HEIGHT:Number = 45;
		
		protected var m_bitmapList:Dictionary = new Dictionary();
		protected var m_loadQueue:Vector.<LoadQueueNode> = new Vector.<LoadQueueNode>();
		protected var m_currentLoadInQueue:String = "";
		
		protected var m_sectorName:String = "sector_00";
		protected var m_decoName:String = "deco_00";
		
		protected var m_index:Point = new Point();
		
		protected var m_boundShape:BitmapData = null;
		
		public function Sector(_container:DisplayObjectContainer) 
		{
			super(_container);
			
			m_bitmapList[k_SECTOR_LAYER_01] = new Bitmap();
			m_bitmapList[k_SECTOR_LAYER_02] = new Bitmap();
			
			m_bitmapList[k_SECTOR_LAYER_02].y -= k_SECTOR_HEIGHT / 2;
			
			this.addChild(m_bitmapList[k_SECTOR_LAYER_01]);
			this.addChild(m_bitmapList[k_SECTOR_LAYER_02]);
			
			super.LoadBoundData(k_SECTOR_DEFAULT_NAME);
		}
		
		override public function Load(_name:String, _sectorType:String):void 
		{
			
			if (_name.search(k_SECTOR_NAME) >= 0)
			{
				m_sectorName = _name;
			}

			if (_name.search(k_DECO_NAME) >= 0)
			{
				m_decoName = _name;
			}
			
			if (m_currentLoadInQueue.length == 0)
			{
				m_currentLoadInQueue = _sectorType;
				super.Load(_name, _sectorType);
			}
			else
			{
				m_loadQueue.push(new LoadQueueNode(_name,_sectorType));
			}
		}
		
		override protected function onLoadResource(_data:BitmapData):void 
		{
			switch( m_currentLoadInQueue )
			{
				case k_SECTOR_LAYER_01 :
				{
					(m_bitmapList[k_SECTOR_LAYER_01] as Bitmap).bitmapData = _data;
				}
				break;
				
				case k_SECTOR_LAYER_02 :
				{
					if (m_decoName != k_DECO_DEFAULT_NAME)
					{
						(m_bitmapList[k_SECTOR_LAYER_02] as Bitmap).bitmapData = _data;
					}
					else
					{
						(m_bitmapList[k_SECTOR_LAYER_02] as Bitmap).bitmapData = null;
					}
				}
				break;
				
				default :
				{
					throw Error;
				}
			}
			
			m_currentLoadInQueue = "";
			
			if (m_loadQueue.length > 0)
			{
				var node:LoadQueueNode = m_loadQueue.pop();
				Load(node.m_name, node.m_type);	
			}
		}
		
		override protected function onLoadBoundData(_data:BitmapData):void 
		{
			m_boundShape = _data;
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
				
				if (Global.editorController.pickBookmarkName == EditorController.k_SECTOR_EDIT_MODE)
				{
				
					if ( m_sectorName == k_SECTOR_NAME + Global.editorController.pickSectorName )
						return;
					
					if ( (k_SECTOR_NAME + Global.editorController.pickSectorName) == k_SECTOR_DEFAULT_NAME )
					{
						Global.editorController.addLog(EditorController.k_EDIT_REMOVE, m_index, k_SECTOR_LAYER_01, m_sectorName, "");
						Global.editorController.removeSector(m_index, k_SECTOR_LAYER_01);
						return;
					}
					
					if (m_sectorName == k_SECTOR_DEFAULT_NAME) 
					{
						Global.editorController.addLog(EditorController.k_EDIT_ADD, m_index, k_SECTOR_LAYER_01, k_SECTOR_NAME + Global.editorController.pickSectorName, "");
						Global.editorController.addSector( m_index, k_SECTOR_NAME + Global.editorController.pickSectorName, k_SECTOR_LAYER_01 );
					}
					else
					{
						Global.editorController.addLog(EditorController.k_EDIT_CHANGE, m_index, k_SECTOR_LAYER_01, k_SECTOR_NAME + Global.editorController.pickSectorName, m_sectorName);
						Global.editorController.changeSector( m_index, k_SECTOR_NAME + Global.editorController.pickSectorName, k_SECTOR_LAYER_01 );
					}
				}
				
				if (Global.editorController.pickBookmarkName == EditorController.k_DECO_EDIT_MODE)
				{
					if ( (m_decoName == k_DECO_NAME + Global.editorController.pickDecoName) || ( m_sectorName == k_SECTOR_DEFAULT_NAME ) )
						return;
					
					if ( (k_DECO_NAME + Global.editorController.pickDecoName) == k_DECO_DEFAULT_NAME )
					{
						Global.editorController.addLog(EditorController.k_EDIT_REMOVE, m_index, k_SECTOR_LAYER_02, m_decoName, "");
						Global.editorController.removeSector(m_index, k_SECTOR_LAYER_02);
						return;
					}
					
					if (m_decoName == k_DECO_DEFAULT_NAME) 
					{
						Global.editorController.addLog(EditorController.k_EDIT_ADD, m_index, k_SECTOR_LAYER_02, k_DECO_NAME + Global.editorController.pickDecoName, "");
						Global.editorController.addSector( m_index, k_DECO_NAME + Global.editorController.pickDecoName, k_SECTOR_LAYER_02 );
					}
					else
					{
						Global.editorController.addLog(EditorController.k_EDIT_CHANGE, m_index, k_SECTOR_LAYER_02, k_DECO_NAME + Global.editorController.pickDecoName, m_decoName);
						Global.editorController.changeSector( m_index, k_DECO_NAME + Global.editorController.pickDecoName, k_SECTOR_LAYER_02 );
					}
				}
			}
		}
		
		protected function isIntersect(_x:Number, _y:Number):uint
		{
			if (m_boundShape != null)
			{
				var mouseLocalPosition:Point = globalToLocal(new Point( _x, _y ));
				return m_boundShape.getPixel(mouseLocalPosition.x, mouseLocalPosition.y);
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
				case k_SECTOR_LAYER_01 :
				{
					(m_bitmapList[k_SECTOR_LAYER_01] as Bitmap).bitmapData = null;
					(m_bitmapList[k_SECTOR_LAYER_02] as Bitmap).bitmapData = null;
					m_boundShape = null;
				}
				break;
				
				case k_SECTOR_LAYER_02 :
				{
					(m_bitmapList[k_SECTOR_LAYER_02] as Bitmap).bitmapData = null;
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
		
		public function get decoName():String 
		{
			return m_decoName;
		}
		
		public function set decoName(_value:String):void
		{
			m_decoName = _value;
		}
	}

}

class LoadQueueNode
{
	public var m_name:String = "";
	public var m_type:String = "";
	
	public function LoadQueueNode(_name:String, _type:String)
	{
		m_name = _name;
		m_type = _type;
	}
}