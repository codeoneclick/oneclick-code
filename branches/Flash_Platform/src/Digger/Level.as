package Digger 
{
	import flash.geom.Point;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Level
	{
		public static var m_Playground:Array;
		
		private var m_MapData:String = "00111111111111" +
									   "00110000011111" +
									   "11111111011111" +
									   "11110011011111" +
									   "11110011011111" +
									   "11100001010001" +
									   "11101111010001" +
									   "11101111010001" +
									   "11100000011111" +
									   "11111111111111";
		
		public function Level() 
		{
			
		}
		
		public function Load():void
		{
			m_Playground = new Array(DiggerSetting.m_PlaygroundHeight);
			for (var i:int = 0; i < DiggerSetting.m_PlaygroundWidth; ++i)
			{
				m_Playground[i] = new Array(DiggerSetting.m_PlaygroundWidth)
				for (var j:int = 0; j < DiggerSetting.m_PlaygroundHeight; ++j)
				{
					
					if (m_MapData.charCodeAt(i + j * DiggerSetting.m_PlaygroundWidth) == 49)
					{
						m_Playground[i][j] = new Element("element_ground");
					}
					else
					{
						m_Playground[i][j] = new Element("element_empty_01");
					}
				}
			}
			
			for (i = 0; i < DiggerSetting.m_PlaygroundWidth; ++i)
				for (j = 0; j < DiggerSetting.m_PlaygroundHeight; ++j)
				{
					if (m_MapData.charCodeAt(i + j * DiggerSetting.m_PlaygroundWidth) == 48)
					{
						if ((i - 1) >= 0)
							if ((m_Playground[i - 1][j] as Element).GetType() == "element_empty_01")
								(m_Playground[i - 1][j] as Element).RemoveEdge("LEFT");
						if ((i + 1) < DiggerSetting.m_PlaygroundWidth)
							if ((m_Playground[i + 1][j] as Element).GetType() == "element_empty_01")
								(m_Playground[i + 1][j] as Element).RemoveEdge("RIGHT");
						if ((j - 1) >= 0)
							if ((m_Playground[i][j - 1] as Element).GetType() == "element_empty_01")
								(m_Playground[i][j - 1] as Element).RemoveEdge("DOWN");
						if ((j + 1) < DiggerSetting.m_PlaygroundHeight)
							if ((m_Playground[i][j + 1] as Element).GetType() == "element_empty_01")
								(m_Playground[i][j + 1] as Element).RemoveEdge("UP");
						
						(m_Playground[i][j] as Element).SetType("element_empty_01");
					}
					(m_Playground[i][j] as Element).m_Position = new Point(i * DiggerSetting.m_ElementWidth, j * DiggerSetting.m_ElementHeight);
					(m_Playground[i][j] as Element).Update();
				}
		}
		
	}

}