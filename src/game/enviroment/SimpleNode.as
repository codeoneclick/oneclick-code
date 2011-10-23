package game.enviroment 
{
	import common.helper3d.Sprite3d;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filters.BlurFilter;
	import flash.filters.GlowFilter;
	import flash.geom.Point;
	import game.core.Core;
	import game.core.Resource;
	/**
	 * ...
	 * @author ...
	 */
	public class SimpleNode extends Sprite3d
	{
		protected var m_bitamData:BitmapData = null;
		protected var m_resName:String = "";
		
		public function SimpleNode(_container:DisplayObjectContainer, _size:Point, _resName:String) 
		{
			super(_container, _size, Sprite3d.k_ALIGN_CENTER);
			m_resName = _resName;
			init();
		}
		
		private function init():void
		{
			Resource.bitmapLoader.Load(m_resName, onResLoad);
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
		
		protected function onResLoad(_data:BitmapData):void
		{
			m_bitamData = _data;
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
		
		protected function onUpdate(_event:Event):void
		{
			update();
			rasterize();
		}	
	}
}