package game 
{
	import common.helper3d.Sprite3d;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author ...
	 */
	public class Tile extends Sprite3d
	{
		protected var m_index:Point = null;
		protected var m_bitamData:BitmapData = null;
		protected var m_resName:String = "";
		
		public function Tile(_container:DisplayObjectContainer, _size:Point, _name:String, _index:Point) 
		{
			super(_container, _size);
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
			m_bitamData = new BitmapData(_data.width / Main.k_MAP_WIDTH, _data.height / Main.k_MAP_HEIGHT);
			m_bitamData.copyPixels(_data, new Rectangle(m_index.x * m_bitamData.width,  m_index.y * m_bitamData.height, m_bitamData.width, m_bitamData.height), new Point(0,0));
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
		}
		
		override protected function onMouseOver(_event:MouseEvent):void 
		{
			super.onMouseOver(_event);
		}
		
		private function onUpdate(_event:Event):void
		{
			update();
			rasterize();
		}
		
	}

}