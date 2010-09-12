package Digger 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Timer;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Explosion
	{
		private var m_Position:Array;
		private var m_Vector:Array;
		
		public var m_ExplosionBlock:Array;
		public var m_DeltaPosition:Point;
		private var m_ExplosionBitmapData:Array;
		
		private var m_LiveTimer:Timer;
		
		public function Explosion(Position:Point) 
		{
			m_ExplosionBlock = new Array(4);
			m_ExplosionBitmapData = new Array(4);
			m_Position = new Array();
			m_Vector = new Array();
			m_DeltaPosition = new Point(0, 0);
			
			for (var i:int = 0; i < 4; ++i)
			{
				m_ExplosionBitmapData[i] = new BitmapData(DiggerSetting.m_ElementWidth/2, DiggerSetting.m_ElementHeight/2);
				m_ExplosionBlock[i] = new Bitmap(m_ExplosionBitmapData[i]);			
				(m_ExplosionBlock[i] as Bitmap).alpha = 1.0;
				m_Position[i] = new Point(Position.x,Position.y);
				DiggerGame.AddToRender(m_ExplosionBlock[i]);
			}	
			
			m_ExplosionBitmapData[0].copyPixels(Resource.m_ContainerPNG["element_explosion"], new Rectangle(0, 0, DiggerSetting.m_ElementWidth / 2, DiggerSetting.m_ElementHeight / 2), new Point(0, 0));
			(m_ExplosionBlock[0] as Bitmap).x = m_Position[0].x;
			(m_ExplosionBlock[0] as Bitmap).y = m_Position[0].y;
			m_Vector[0] = new Point(-4, -4);
			m_ExplosionBitmapData[1].copyPixels(Resource.m_ContainerPNG["element_explosion"], new Rectangle(DiggerSetting.m_ElementWidth / 2, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight / 2), new Point(0, 0));
			m_Position[1].x += DiggerSetting.m_ElementWidth / 2;
			(m_ExplosionBlock[1] as Bitmap).x = m_Position[1].x;
			(m_ExplosionBlock[1] as Bitmap).y = m_Position[1].y;
			m_Vector[1] = new Point(4, -4);
			m_ExplosionBitmapData[2].copyPixels(Resource.m_ContainerPNG["element_explosion"], new Rectangle(0, DiggerSetting.m_ElementHeight / 2, DiggerSetting.m_ElementWidth / 2, DiggerSetting.m_ElementHeight), new Point(0, 0));
			m_Position[2].y += DiggerSetting.m_ElementHeight / 2;
			(m_ExplosionBlock[2] as Bitmap).x = m_Position[2].x;
			(m_ExplosionBlock[2] as Bitmap).y = m_Position[2].y;
			m_Vector[2] = new Point(-4, 4);
			m_ExplosionBitmapData[3].copyPixels(Resource.m_ContainerPNG["element_explosion"], new Rectangle(DiggerSetting.m_ElementWidth / 2, DiggerSetting.m_ElementHeight / 2, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, 0));
			m_Position[3].x += DiggerSetting.m_ElementWidth / 2;
			m_Position[3].y += DiggerSetting.m_ElementHeight / 2;
			(m_ExplosionBlock[3] as Bitmap).x = m_Position[3].x;
			(m_ExplosionBlock[3] as Bitmap).y = m_Position[3].y;
			m_Vector[3] = new Point(4, 4);
			
			m_LiveTimer = new Timer(30,15);
			m_LiveTimer.addEventListener(TimerEvent.TIMER, Update);
			m_LiveTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnEnd);
			m_LiveTimer.start();
		}
		
		private function Update(event:TimerEvent):void
		{
			for (var i:int = 0; i < 4; ++i)
			{
				m_Position[i].x += m_Vector[i].x;
				m_Position[i].y += m_Vector[i].y;
				
				(m_ExplosionBlock[i] as Bitmap).x = m_Position[i].x + m_DeltaPosition.x;
				(m_ExplosionBlock[i] as Bitmap).y = m_Position[i].y + m_DeltaPosition.y;
				(m_ExplosionBlock[i] as Bitmap).alpha -= 0.075;
			}
		}
		
		private function OnEnd(event:TimerEvent):void
		{
			m_LiveTimer.stop();
			m_LiveTimer = null;
			for (var i:int = 0; i < 4; ++i)
			{
				DiggerGame.RemoveFromRender(m_ExplosionBlock[i]);
				m_ExplosionBitmapData[i] = null;
				m_ExplosionBlock[i] = null;
			}
			delete this;
		}
	}

}