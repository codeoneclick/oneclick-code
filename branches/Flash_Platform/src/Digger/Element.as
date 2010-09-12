package Digger 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.BlendMode;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	import flash.utils.Dictionary;
	import flash.utils.Timer;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Element
	{
		
		public  var m_Position:Point;
		private var m_Edging:Dictionary;
		private var m_Type:String;
		private var m_RequestType:String;
		private var m_IsVisit:Boolean = false;
		private var m_SwitchTypeTimer:Timer;
		private var m_DeltaSwitch:uint = 0;
		private var m_BitmapData:BitmapData;
		private var m_RequestBitmapData:BitmapData;
		
		public function Element(Type:String) 
		{
			m_Edging = new Dictionary();
			m_Edging["UP"]    = true;
			m_Edging["DOWN"]  = true;
			m_Edging["LEFT"]  = true;
			m_Edging["RIGHT"] = true;
			m_Type = Type;
			
			m_BitmapData = new BitmapData(DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight);
			m_BitmapData.draw(Resource.m_ContainerPNG[m_Type]);
			
			m_RequestBitmapData = new BitmapData(DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight);
			
			m_SwitchTypeTimer = new Timer(70,10);
			m_SwitchTypeTimer.addEventListener(TimerEvent.TIMER, OnSwitchType);
			m_SwitchTypeTimer.addEventListener(TimerEvent.TIMER_COMPLETE, OnSwitchEnd);
		}
		
		public function RemoveEdge(value:String):void
		{
			m_Edging[value] = false;
		}
		
		public function SetType(Type:String):void
		{
			m_DeltaSwitch = 0;
			m_RequestType = Type;
			m_RequestBitmapData.draw(Resource.m_ContainerPNG[m_RequestType]);
			m_SwitchTypeTimer.reset();
			m_SwitchTypeTimer.start();
		}
		
		private function OnSwitchType(event:TimerEvent):void
		{
			m_BitmapData.merge(m_RequestBitmapData, new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, 0), m_DeltaSwitch, m_DeltaSwitch, m_DeltaSwitch, 0);
			if (m_Edging["UP"] == true)
				{
					m_BitmapData.merge(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_EdgeWidth), new Point(0, 0),m_DeltaSwitch, m_DeltaSwitch, m_DeltaSwitch, 0);
				}
				if (m_Edging["DOWN"] == true)
				{
					m_BitmapData.merge(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, DiggerSetting.m_ElementHeight - DiggerSetting.m_EdgeWidth, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, DiggerSetting.m_ElementHeight - DiggerSetting.m_EdgeWidth),m_DeltaSwitch, m_DeltaSwitch, m_DeltaSwitch, 0);
				}
				if (m_Edging["LEFT"] == true)
				{
					m_BitmapData.merge(Resource.m_ContainerPNG["element_stone"], new Rectangle(DiggerSetting.m_ElementWidth - DiggerSetting.m_EdgeWidth, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(DiggerSetting.m_ElementWidth - DiggerSetting.m_EdgeWidth,0),m_DeltaSwitch, m_DeltaSwitch, m_DeltaSwitch, 0);
				}
				if (m_Edging["RIGHT"] == true)
				{
					m_BitmapData.merge(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, 0, DiggerSetting.m_EdgeWidth, DiggerSetting.m_ElementHeight ), new Point(0, 0),m_DeltaSwitch, m_DeltaSwitch, m_DeltaSwitch, 0);
				}
			DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(m_BitmapData, new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(m_Position.x, m_Position.y));
			m_DeltaSwitch += 20;
			
		}
		
		private function OnSwitchEnd(event:TimerEvent):void
		{
			m_Type = m_RequestType;
			m_IsVisit = true;
			//Player.Add();
		}
		
		public function Update():void
		{
			DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(m_BitmapData, new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(m_Position.x, m_Position.y));
			
			/*if (m_IsVisit)
			{
				if (m_Edging["UP"] == true)
				{
					DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_EdgeWidth), new Point(m_Position.x, m_Position.y));
				}
				if (m_Edging["DOWN"] == true)
				{
					DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, DiggerSetting.m_ElementHeight - DiggerSetting.m_EdgeWidth, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(m_Position.x, m_Position.y + (DiggerSetting.m_ElementHeight - DiggerSetting.m_EdgeWidth)));
				}
				if (m_Edging["LEFT"] == true)
				{
					DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(Resource.m_ContainerPNG["element_stone"], new Rectangle(DiggerSetting.m_ElementWidth - DiggerSetting.m_EdgeWidth, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(m_Position.x + (DiggerSetting.m_ElementWidth - DiggerSetting.m_EdgeWidth), m_Position.y));
				}
				if (m_Edging["RIGHT"] == true)
				{
					DiggerGame.m_PlaygroundLayerBitmapData.copyPixels(Resource.m_ContainerPNG["element_stone"], new Rectangle(0, 0, DiggerSetting.m_EdgeWidth, DiggerSetting.m_ElementHeight ), new Point(m_Position.x, m_Position.y));
				}
			}*/
		}
		
	}

}