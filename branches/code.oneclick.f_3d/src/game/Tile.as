package game 
{
	import common.helper3d.Sprite3d;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filters.BlurFilter;
	import flash.filters.GlowFilter;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author ...
	 */
	public class Tile extends Sprite3d
	{
		public static const k_TILE_WIDTH:int = 64;
		public static const k_TILE_HEIGHT:int = 64;
		
		protected var m_index:Point = null;
		protected var m_bitamData:BitmapData = null;
		protected var m_resName:String = "";
		
		protected var m_intersect:Boolean = false;
		
		public function Tile(_container:DisplayObjectContainer, _size:Point, _name:String, _index:Point) 
		{
			super(_container, _size, Sprite3d.k_ALIGN_CENTER);
			m_index = _index;
			m_resName = _name;
			init();
		}
		
		private function init():void
		{
			Core.bitmapLoader.Load(m_resName, onResLoad);
			addEventListener(Event.ENTER_FRAME, onUpdate);
		}
		
		override protected function rasterize():void 
		{
			if (m_bitamData == null)
			{
				return;
			}
			super.rasterize();
		}
		
		private function onResLoad(_data:BitmapData):void
		{
			m_bitamData = _data;
			//new BitmapData(_data.width , _data.height);
			//m_bitamData.copyPixels(_data, new Rectangle(m_index.x * m_bitamData.width,  m_index.y * m_bitamData.height, m_bitamData.width, m_bitamData.height), new Point(0,0));
			m_texture.size = new Point(m_bitamData.width, m_bitamData.height);
			m_texture.bitmapData = m_bitamData;
		}
		
		override protected function update():void
		{
			super.update();
		}
		
		override protected function onMouseOut(_event:MouseEvent):void 
		{
			super.onMouseOut(_event);
			m_intersect = false;
		}
		
		override protected function onMouseOver(_event:MouseEvent):void 
		{
			super.onMouseOver(_event);
			m_intersect = true;
		}
		
		private function onUpdate(_event:Event):void
		{
			onUpdateLogic();
			
			update();
			rasterize();
		}
		
		private function onUpdateLogic():void
		{
			if (m_intersect)
			{
				filters = [new GlowFilter(0x000000,1,6,6,6,1,true)];
			}
			else
			{
				filters = [];
			}
		}
		
	}

}