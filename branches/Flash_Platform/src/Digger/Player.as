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
	public class Player
	{
		public  static var m_Position:Point;
		public  static var m_PositionIndex:Point;
		private var m_MoveToIndex:Point;
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
		
		public function Player() 
		{
			m_Position = new Point(0, 0);
			m_PositionIndex = new Point(0, 0);
			m_MoveToIndex = new Point(0, 0);
			m_MovePointPosition = new Point(0, 0);
			m_DeltaMovePosition = new Point(0, 0);
			m_IsMove = false;
			m_Speed = 4;
			m_DirectionType = "NONE";
			m_BitmapData = new BitmapData(DiggerSetting.m_ElementWidth , DiggerSetting.m_ElementHeight );
			m_Bitmap = new Bitmap(m_BitmapData);	
			m_BitmapData.copyPixels(Resource.m_ContainerPNG["element_player"], new Rectangle(0, 0, DiggerSetting.m_ElementWidth, DiggerSetting.m_ElementHeight), new Point(0, 0));
			m_BitmapContainer = new Sprite();
			m_Bitmap.x = -m_Bitmap.width / 2;
			m_Bitmap.y = -m_Bitmap.height / 2;
			m_BitmapContainer.scaleX = new Number(0.6);
			m_BitmapContainer.scaleY = new Number(0.6);
			m_BitmapContainer.filters = [getBitmapFilter()];
			m_BitmapContainer.addChild(m_Bitmap);
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
		
		public static function Add():void
		{
			m_CurrentExplosion = new Explosion(new Point(m_Position.x, m_Position.y));
		}

		
		public function MoveUp():void
		{
			if (m_PositionIndex.y == 0 || m_IsMove) 
				return;
			m_MoveToIndex.y--;
			m_MovePointPosition.y -= DiggerSetting.m_ElementHeight;
			m_IsMove = true;
			m_DirectionType = "UP";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_CurrentExplosion = new Explosion(new Point(m_Position.x, m_Position.y - DiggerSetting.m_ElementHeight / 2));
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).RemoveEdge("UP");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).RemoveEdge("DOWN");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).Update();
			m_BitmapContainer.rotation = 90;
		}
		
		public function MoveDown():void
		{
			if (m_PositionIndex.y == (DiggerSetting.m_PlaygroundHeight - 1) || m_IsMove) 
				return;
			m_MoveToIndex.y++;
			m_MovePointPosition.y += DiggerSetting.m_ElementHeight;
			m_IsMove = true;
			m_DirectionType = "DOWN";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_CurrentExplosion = new Explosion(new Point(m_Position.x, m_Position.y + DiggerSetting.m_ElementHeight / 2));
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).RemoveEdge("DOWN");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).RemoveEdge("UP");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).Update();
			m_BitmapContainer.rotation = -90;
		}
		
		public function MoveLeft():void
		{
			if (m_PositionIndex.x == (DiggerSetting.m_PlaygroundWidth - 1) || m_IsMove) 
				return;
			m_MoveToIndex.x++;
			m_MovePointPosition.x += DiggerSetting.m_ElementWidth;
			m_IsMove = true;
			m_DirectionType = "LEFT";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_CurrentExplosion = new Explosion(new Point(m_Position.x + DiggerSetting.m_ElementWidth / 2, m_Position.y));
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).RemoveEdge("LEFT");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).RemoveEdge("RIGHT");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).Update();
			m_BitmapContainer.rotation = 0;
		}
		
		public function MoveRight():void
		{
			if (m_PositionIndex.x == 0 || m_IsMove) 
				return;
			m_MoveToIndex.x--;
			m_MovePointPosition.x -= DiggerSetting.m_ElementWidth;
			m_IsMove = true;
			m_DirectionType = "RIGHT";
			m_DeltaMovePosition.x = 0;
			m_DeltaMovePosition.y = 0;
			m_CurrentExplosion = new Explosion(new Point(m_Position.x - DiggerSetting.m_ElementWidth / 2, m_Position.y));
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).RemoveEdge("RIGHT");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).RemoveEdge("LEFT");
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).SetType("element_empty_01");
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
			(DiggerGame.m_Playground[m_MoveToIndex.x][m_MoveToIndex.y] as Element).Update();
			
			m_BitmapContainer.rotation = 180;
		}
		
		public function Update():void
		{
			switch(m_DirectionType)
			{
				case "UP" :
					if (m_DeltaMovePosition.y > -DiggerSetting.m_ElementHeight)
					{
						if (m_Position.y < Setting.m_Height / 2 && DiggerGame.m_PlaygroundBitmap.y < 0)
						{
							DiggerGame.m_PlaygroundBitmap.y += m_Speed;
							m_CurrentExplosion.m_DeltaPosition.y += m_Speed;
						}
						else
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
						if (m_Position.y > Setting.m_Height / 2 && DiggerGame.m_PlaygroundBitmap.y > -Setting.m_Height)
						{
							DiggerGame.m_PlaygroundBitmap.y -= m_Speed;
							m_CurrentExplosion.m_DeltaPosition.y -= m_Speed;
						}
						else
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
						
						if (m_Position.x > Setting.m_Width / 2  && DiggerGame.m_PlaygroundBitmap.x > -Setting.m_Width)
						{
							DiggerGame.m_PlaygroundBitmap.x -= m_Speed;
							m_CurrentExplosion.m_DeltaPosition.x -= m_Speed;
						}
						else
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
						if (m_Position.x < Setting.m_Width / 2 && DiggerGame.m_PlaygroundBitmap.x < 0)
						{
							DiggerGame.m_PlaygroundBitmap.x += m_Speed;
							m_CurrentExplosion.m_DeltaPosition.x += m_Speed;
						}
						else
							m_Position.x -= m_Speed; 
						m_DeltaMovePosition.x -= m_Speed;
					}
					else
					{
						MoveEnd();
					}
				break;
			}
			
			m_BitmapContainer.x = m_Position.x + m_Bitmap.width / 2;
			m_BitmapContainer.y = m_Position.y + m_Bitmap.height / 2;
		}
		
		private function MoveEnd():void
		{
			m_IsMove = false;
			m_PositionIndex = new Point(m_MoveToIndex.x, m_MoveToIndex.y);
			m_DirectionType = "NONE";
			(DiggerGame.m_Playground[m_PositionIndex.x][m_PositionIndex.y] as Element).Update();
		}
		
	}

}