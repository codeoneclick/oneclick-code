package Digger 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.filters.BitmapFilter;
	import flash.filters.BitmapFilterQuality;
    import flash.filters.DropShadowFilter;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Enemy
	{
		public  var m_Position:Point;
		public  var m_PositionIndex:Point;
		public var m_MoveToIndex:Point;
		private var m_MovePointPosition:Point;
		private var m_DirectionType:String; 
		private var m_FramesCount:int;
		private var m_CurrentFrame:int;
		private var m_IsMove:Boolean;
		private var m_BitmapData:BitmapData;
		private  var m_Bitmap:Bitmap;
		public  var m_BitmapContainer:Sprite;
		private var m_Speed:int;
		private var m_DeltaMovePosition:Point;
		private static var m_CurrentExplosion:Explosion;
		private var m_AnimController:AnimController = null;
		
		public function Enemy() 
		{
			m_Position = new Point(4*DiggerSetting.m_ElementHeight, 1 * DiggerSetting.m_ElementHeight);
			m_PositionIndex = new Point(4, 1);
			m_MoveToIndex = new Point(4,1);
			m_MovePointPosition = new Point(0, 0);
			m_DeltaMovePosition = new Point(0, 0);
			m_IsMove = false;
			m_Speed = 1;
			m_DirectionType = "NONE";
			m_BitmapData = new BitmapData(DiggerSetting.m_ElementWidth , DiggerSetting.m_ElementHeight );
			m_Bitmap = new Bitmap(m_BitmapData);	
			//m_BitmapData.copyPixels(Resource.m_ContainerPNG["e01_move_0"], new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, 0));
			m_BitmapContainer = new Sprite();
			m_Bitmap.x = -m_Bitmap.width / 2;
			m_Bitmap.y = -m_Bitmap.height / 2;
			m_BitmapContainer.scaleX = new Number(0.6);
			m_BitmapContainer.scaleY = new Number(0.6);
			m_BitmapContainer.addChild(m_Bitmap);
			
			m_BitmapContainer.filters = [getBitmapFilter()];
			
			m_AnimController = new AnimController(m_BitmapData);
			m_AnimController.AddAnim("e01_move_", 20);
			m_AnimController.StartAnim("e01_move_", true);
		}
		
		private function getBitmapFilter():BitmapFilter {
            var color:Number = 0x000000;
            var angle:Number = 45;
            var alpha:Number = 1.0;
            var blurX:Number = 2;
            var blurY:Number = 2;
            var distance:Number = 10;
            var strength:Number = 0.8;
            var inner:Boolean = false;
            var knockout:Boolean = false;
            var quality:Number = BitmapFilterQuality.HIGH;
            return new DropShadowFilter(distance,
                                        angle,
                                        color,
                                        alpha,
                                        blurX,
                                        blurY,
                                        strength,
                                        quality,
                                        inner,
                                        knockout);
        }
		
		public function MoveUp():void
		{
			if (m_PositionIndex.y == 0 || m_IsMove) 
				return;
			if ((Level.m_Playground[m_PositionIndex.x][m_PositionIndex.y - 1] as Element).GetType() == "element_ground")
				return;
			if ((Level.m_Playground[m_PositionIndex.x][m_PositionIndex.y - 1] as Element).m_Edging["DOWN"] == true)
				return;
			m_MoveToIndex.y--;
			m_MovePointPosition.y -= DiggerSetting.m_ElementHeight;
			m_IsMove = true;
			m_DirectionType = "UP";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_BitmapContainer.rotation = -90;
		}
		
		public function MoveDown():void
		{
			if (m_PositionIndex.y == (DiggerSetting.m_PlaygroundHeight - 1) || m_IsMove) 
				return;
			if ((Level.m_Playground[m_PositionIndex.x][m_PositionIndex.y + 1] as Element).GetType() == "element_ground")
				return;
			if ((Level.m_Playground[m_PositionIndex.x][m_PositionIndex.y + 1] as Element).m_Edging["UP"] == true)
				return;
			m_MoveToIndex.y++;
			m_MovePointPosition.y += DiggerSetting.m_ElementHeight;
			m_IsMove = true;
			m_DirectionType = "DOWN";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_BitmapContainer.rotation = 90;
		}
		
		public function MoveLeft():void
		{
			if (m_PositionIndex.x == (DiggerSetting.m_PlaygroundWidth - 1) || m_IsMove) 
				return;
			if ((Level.m_Playground[m_PositionIndex.x + 1][m_PositionIndex.y] as Element).GetType() == "element_ground")
				return;
			if ((Level.m_Playground[m_PositionIndex.x + 1][m_PositionIndex.y] as Element).m_Edging["RIGHT"] == true)
				return;
			m_MoveToIndex.x++;
			m_MovePointPosition.x += DiggerSetting.m_ElementWidth;
			m_IsMove = true;
			m_DirectionType = "LEFT";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_BitmapContainer.rotation = 0;
		}
		
		public function MoveRight():void
		{
			if (m_PositionIndex.x == 0 || m_IsMove) 
				return;
			if ((Level.m_Playground[m_PositionIndex.x - 1][m_PositionIndex.y] as Element).GetType() == "element_ground")
				return;
			if ((Level.m_Playground[m_PositionIndex.x - 1][m_PositionIndex.y] as Element).m_Edging["LEFT"] == true)
				return;
			m_MoveToIndex.x--;
			m_MovePointPosition.x -= DiggerSetting.m_ElementWidth;
			m_IsMove = true;
			m_DirectionType = "RIGHT";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_BitmapContainer.rotation = 180;
		}
		
		public function Update():void
		{
			
			var RandomDirection:Number = Math.random() * 100;
			
			if (RandomDirection < 25)
				MoveUp();
			if (RandomDirection >= 25 && RandomDirection < 50)
				MoveRight();
			if (RandomDirection >= 50 && RandomDirection < 75)
				MoveLeft();
			if (RandomDirection >= 75 && RandomDirection <= 100)
				MoveDown();
			
			switch(m_DirectionType)
			{
				case "UP" :
					if (m_DeltaMovePosition.y > -DiggerSetting.m_ElementHeight)
					{
						m_Position.y -= m_Speed;
						m_DeltaMovePosition.y -= m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "DOWN" :
					if (m_DeltaMovePosition.y < DiggerSetting.m_ElementHeight)
					{
						m_Position.y += m_Speed;
						m_DeltaMovePosition.y += m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "LEFT" :
					if (m_DeltaMovePosition.x < DiggerSetting.m_ElementWidth)
					{
						m_Position.x += m_Speed;
						m_DeltaMovePosition.x += m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
				case "RIGHT" :
					if (m_DeltaMovePosition.x > -DiggerSetting.m_ElementWidth)
					{
						m_Position.x -= m_Speed; 
						m_DeltaMovePosition.x -= m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
			}
			
			m_BitmapContainer.x = m_Position.x + m_Bitmap.width / 2 + DiggerGame.m_PlaygroundBitmap.x;
			m_BitmapContainer.y = m_Position.y + m_Bitmap.height / 2 +  DiggerGame.m_PlaygroundBitmap.y;
		}
		
		private function MoveEnd():void
		{
			m_IsMove = false;
			m_PositionIndex = new Point(m_MoveToIndex.x, m_MoveToIndex.y);
			m_DirectionType = "NONE";
			(Level.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
		}
		
	}

}