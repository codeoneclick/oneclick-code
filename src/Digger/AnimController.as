package Digger 
{
	import flash.accessibility.AccessibilityProperties;
	import flash.display.BitmapData;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Dictionary;
	import flash.utils.Timer;
	/**
	 * ...
	 * @author ...
	 */
	public class AnimController
	{
		private var m_List:Dictionary = new Dictionary();
		private var m_SourceBitmapData:BitmapData = null;
		
		private var m_Timer:Timer = null;
		private var m_Speed:uint = 45;
		
		public function set Speed(value:uint):void
		{
			m_Speed = value;
		}
		
		private var m_Loop:Boolean = true;
		private var m_CurrentName:String = null;
		private var m_CurrentFrame:uint = 0;
		
		public function AnimController(sourceBitmapData:BitmapData) 
		{
			m_SourceBitmapData = sourceBitmapData;
			m_Timer = new Timer(m_Speed);
			m_Timer.addEventListener(TimerEvent.TIMER, OnAnim);
			m_Timer.start();
		}
		
		public function AddAnim(name:String, frames:uint):void
		{
			m_List[name] = frames;
		}
		
		public function StartAnim(name:String, loop:Boolean):void
		{
			if ( name == m_CurrentName ) return;
			if ( !m_Loop ) return;
			
			m_CurrentName = name;
			m_Loop = loop;
			m_CurrentFrame = 0;
		}
		
		private function OnAnim(event:TimerEvent):void
		{
			m_SourceBitmapData.copyPixels(Resource.m_ContainerPNG[m_CurrentName + m_CurrentFrame.toString()], new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, 0));
			m_CurrentFrame++;
			if (m_CurrentFrame == m_List[m_CurrentName])
			{
				m_Loop = true;
				m_CurrentFrame = 0;
			}
		}
		
	}

}