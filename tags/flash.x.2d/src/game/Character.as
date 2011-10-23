package game 
{
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.filters.GlowFilter;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class Character extends GameNode
	{
		private static const k_ANIMATION_MOVE:String = "ANIMATION_MOVE";
		
		protected var m_direction:int = 0;
		
		protected var m_animationSequence:Dictionary = new Dictionary();
		
		protected var m_framesCount:int = 0;
		protected var m_currentFrame:int = 0;
		
		public function Character(_container:DisplayObjectContainer) 
		{
			super(_container);
		}
		
		override protected function onLoadResource(_data:BitmapData):void 
		{
			super.onLoadResource(_data);
			m_animationSequence[k_ANIMATION_MOVE] = new Vector.<BitmapData>;
			for ( var i:int  = 0; i < 4; i++ )
			{
				for ( var j:int  = 0; j < 2; j++ )
				{
					var bitmapData:BitmapData = new BitmapData( 64, 64 );
					bitmapData.copyPixels(_data, new Rectangle( i * 64, j * 64, i * 64 + 64, j * 64 + 64 ), new Point( 0, 0 ) );
					m_animationSequence[k_ANIMATION_MOVE].push(bitmapData);
					m_framesCount++;
				}
			}
		}
		
		override protected function onUpdate(_event:Event):void 
		{
			super.onUpdate(_event);
			
			m_currentFrame++;
			
			if ( m_currentFrame >= m_framesCount )
				m_currentFrame = 0;
				
			//if (m_animationSequence[k_ANIMATION_MOVE][m_currentFrame] != null)
			//{
			//	m_bitmap.bitmapData = m_animationSequence[k_ANIMATION_MOVE][m_currentFrame];
			//}
		}
		
		override protected function onIntersectUpdate():void 
		{
			if (m_intersect)
			{
				filters = [new GlowFilter(0x00FFFFFF)];
			}
			else
			{
				filters = null;
			}
		}
		
	}

}