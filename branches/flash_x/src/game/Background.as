package game 
{
	import core.Global;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Background  extends Sprite
	{
		
		protected var m_container:DisplayObjectContainer = null;
		protected var m_bitmap:Bitmap = null;
		
		public function Background(_container:DisplayObjectContainer)  
		{
			m_container = _container;
			m_bitmap = new Bitmap();
			this.addChild(m_bitmap);
			m_container.addChild(this);
		}
		
		public function Load(_name:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadResource);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			m_bitmap.bitmapData = _data;
		}
		
	}

}