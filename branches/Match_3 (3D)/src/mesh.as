package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.display.Loader;
	import flash.geom.Rectangle;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	
	/**
	 * @author PsyTech
	 */
	public class mesh 
	{
		public  var position					:vector; 				// Позиция меша.
		public  var localRotation				:vector;				// Локальный поворот ( вокруг своего центра).
		public  var globalRotation				:vector;				// Глобальный поворот ( вокруг заданного центра).
		public  var size						:Point;					// Размер меша.
		private var sizeHalf					:Point;					// Половинный размер меша, для расчета смещения.
	
		private var pointLeftTop				:vector;				// Точка плоскости в обычных трехмерных коодинатах.
		private var pointLeftBottom				:vector;				// Точка плоскости в обычных трехмерных коодинатах.
		private var pointRightTop				:vector;				// Точка плоскости в обычных трехмерных коодинатах.
		private var pointRightBottom			:vector;				// Точка плоскости в обычных трехмерных коодинатах.
		
		private var isIntersect					:Boolean = false;		// Флаг пересечения меша с курсором мыши.
		public  var isClick    					:Boolean = false;		// Флаг нажатия курсора мишы на меш.

		public	var nonePlane					:MovieClip;				// Мувиклип для отображения пустой плоскости ( без фишек ).
		public	var itemPlane					:MovieClip;				// Мувиклип для отображения фишки на игровой плоскости.

		private var noneTexture					:texture;				// Текстура пустой плоскости.
		private var itemTexture					:texture;				// Текстура фишки.

		public  var screenPointLeftTop			:vector;				// Точка плоскости в screen space ( ортогональных ) коодинатах.
		public  var screenPointLeftBottom		:vector;				// Точка плоскости в screen space ( ортогональных ) коодинатах.
		public  var screenPointRightTop			:vector;				// Точка плоскости в screen space ( ортогональных ) коодинатах.
		public  var screenPointRightBottom		:vector;				// Точка плоскости в screen space ( ортогональных ) коодинатах.

		public  var itemType					:int = 0;				// Тип фишки. Для отображения подходящей картинки.
		public  var panelType					:int = 0;				// Тип ячейки игрового поля. Для отображения подходящей картинки.
		public  var isMove						:Boolean = false;       // Флаг  для визуализации перемещения фишки.
		public  var isMatchPanel				:Boolean = false;		// Флаг для визуализации поля Match.
		private var lastType					:int = 0;				// Сюда запоминаем последнее измененное значение типа, для дальнейшего восстановления.
		
		private var matrixRotationX				:matrix;				// Матрица поворота по оси X;
		private var matrixRotationY				:matrix;				// Матрица поворота по оси Y;
		private var matrixRotationZ				:matrix;				// Матрица поворота по оси Z;
		
		public  var value						:int = 0;				// Значение ячейки поля для поиска пути (вес прохода).
		public  var index						:int = -1;				// Индекс ячейки для генерации исходного пути.
		public  var indexX						:int = -1;				// Идексы для инициализации игрового поля весами проходимости.
		public  var indexY						:int = -1;				// Идексы для инициализации игрового поля весами проходимости.
		
		public  var contentLoader				:ContentLoader; 		// Загрузчик контента, отсюда извлекаем все картинки.
		private var game						:gameMatch3;					// Указатель на обьект игры.
		
		private var skinName					:String;				// Имя текущего скина, для кореектной обработки скинов.
		
		public function mesh(game:gameMatch3) 
		{
			this.game = game;
			this.nonePlane = new MovieClip();
			this.itemPlane = new MovieClip();
			this.screenPointLeftBottom = new vector();
			this.screenPointLeftTop = new vector();
			this.screenPointRightBottom = new vector();
			this.screenPointRightTop = new vector();
			
			this.pointLeftBottom = new vector();
			this.pointLeftTop = new vector();
			this.pointRightBottom = new vector();
			this.pointRightTop = new vector();
			
			this.position = new vector(); 
			this.size = new Point(80, 80);
			this.sizeHalf = new Point(this.size.x / 2, this.size.y / 2);
			
			this.nonePlane.x = 0;
			this.nonePlane.y = 0;
			
			this.globalRotation = new vector();
			this.localRotation = new vector();
			
			this.noneTexture = new texture(this.nonePlane);
			this.itemTexture = new texture(this.itemPlane);
		}
		
		public function createIntersect():void
		{
			this.nonePlane.addEventListener(MouseEvent.MOUSE_OVER, onIntersectIn);
			this.nonePlane.addEventListener(MouseEvent.MOUSE_OUT, onIntersectOut);
			this.nonePlane.addEventListener(MouseEvent.CLICK,     onIntersectClick);
			
			this.itemPlane.addEventListener(MouseEvent.MOUSE_OVER, onIntersectIn);
			this.itemPlane.addEventListener(MouseEvent.MOUSE_OUT, onIntersectOut);
			this.itemPlane.addEventListener(MouseEvent.CLICK,     onIntersectClick);
		}
		
		public function setSkin(name:String):void
		{
			this.skinName = name;
		}
		
		private function onIntersectClick(event:MouseEvent):void
		{
			if (this.itemType > 0)
			{
				this.game.clearClickIntersection();
				this.game.itemPickIndex = this.index;
				this.isClick = true;
			}
			else
				if (this.game.itemPickIndex != -1)
				{
					this.game.panelPickIndex = this.index;
					this.game.findPath();
				}
		}
		
		public function setMovePanel():void
		{
			this.lastType = this.panelType;
			this.panelType = 2;
		}
		
		public function setNonePanel():void
		{
			this.panelType = this.lastType;
		}
	
		private function onIntersectIn(event:MouseEvent):void
		{
			this.isIntersect = true;
		}
		
		private function onIntersectOut(event:MouseEvent):void
		{
			this.isIntersect = false;
		}
		
		public function draw():void
		{
			
			
			switch(this.itemType)
			{
				case 0:
					this.itemPlane.visible = false;
					break;
				case 1:
					if (this.isIntersect == false && this.isClick == false)
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "01MainPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					else
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "01PickPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					break;
				case 2:
					if (this.isIntersect == false && this.isClick == false)
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "02MainPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					else
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "02PickPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					break;
				case 3:
					if (this.isIntersect == false && this.isClick == false)
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "03MainPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					else
					{
						this.itemPlane.visible = true;
						this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "03PickPanel"]);
						this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.itemTexture.render();
					}
					break;
			}
			
			switch(this.panelType)
			{
				case 0:
					if (this.isIntersect == false)
					{
						if (this.isMatchPanel == false)
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MainPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
						else
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MatchPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
					}
					else
					{
						this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "PickPanel"]);
						this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.noneTexture.render();
					}
					break;
				case 1:
					break;
				case 2:
					this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MovePanel"]);
					this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
					this.noneTexture.render();
					break;
				case 3:
					if (this.isIntersect == false)
					{
						if (this.isMatchPanel == false)
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MainPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
						else
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MatchPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
					}
					else
					{
						this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "PickPanel"]);
						this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.noneTexture.render();
					}
					this.itemPlane.visible = true;
					this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "01HalfPanel"]);
					this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
					this.itemTexture.render();
					break;
				case 4:
					if (this.isIntersect == false)
					{
						if (this.isMatchPanel == false)
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MainPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
						else
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MatchPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
					}
					else
					{
						this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "PickPanel"]);
						this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.noneTexture.render();
					}
					this.itemPlane.visible = true;
					this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "02HalfPanel"]);
					this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
					this.itemTexture.render();
					break;
				case 5:
					if (this.isIntersect == false)
					{
						if (this.isMatchPanel == false)
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MainPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
						else
						{
							this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "MatchPanel"]);
							this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
							this.noneTexture.render();
						}
					}
					else
					{
						this.noneTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "PickPanel"]);
						this.noneTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
						this.noneTexture.render();
					}
					this.itemPlane.visible = true;
					this.itemTexture.setSourceImage(this.contentLoader.imagesManager[this.skinName + "03HalfPanel"]);
					this.itemTexture.setTransform(screenPointLeftBottom.x, screenPointLeftBottom.y, screenPointRightBottom.x, screenPointRightBottom.y, screenPointRightTop.x, screenPointRightTop.y, screenPointLeftTop.x, screenPointLeftTop.y);
					this.itemTexture.render();
					break;
			}
		}
		
		public function refresh():void
		{
			pointLeftTop.z = 0;
			pointLeftTop.x = 0;
			pointLeftTop.y = 0;
			////////////////////////////////
			pointRightTop.z = 0;
			pointRightTop.x = sizeHalf.x;
			pointRightTop.y = 0;
			////////////////////////////////
			pointLeftBottom.z = 0;
			pointLeftBottom.x = 0;
			pointLeftBottom.y = sizeHalf.y;
			////////////////////////////////
			pointRightBottom.z = 0;
			pointRightBottom.x = sizeHalf.x;
			pointRightBottom.y = sizeHalf.y;
		}
		
		public function updateIntersect():void
		{	
			this.draw();
		}
		
		public function update():void
		{
			this.refresh();
			this.rotateLocal();
			this.translate();
			
			//this.rotateGlobal();
		}
		
		public function rasterize(matrixProjection:matrix):void
		{
			var d:Number = 1;
			
			var ar:Number = 800 / 600;
			
			screenPointLeftBottom.x = pointLeftBottom.x * d / pointLeftBottom.z;
			screenPointLeftBottom.y = pointLeftBottom.y * d  * ar / pointLeftBottom.z;
			
			screenPointLeftTop.x = pointLeftTop.x * d / pointLeftTop.z;
			screenPointLeftTop.y = pointLeftTop.y * d * ar  / pointLeftTop.z;
			
			screenPointRightBottom.x = pointRightBottom.x * d / pointRightBottom.z;
			screenPointRightBottom.y = pointRightBottom.y * d  * ar  / pointRightBottom.z;
			
			screenPointRightTop.x = pointRightTop.x * d / pointRightTop.z;
			screenPointRightTop.y = pointRightTop.y * d  * ar  / pointRightTop.z;

			
			screenPointLeftBottom.x = (screenPointLeftBottom.x + 1) * (0.5 * 800 - 0.5);
			screenPointLeftBottom.y = ( 600 - 1 ) - ( screenPointLeftBottom.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			screenPointLeftTop.x = (screenPointLeftTop.x + 1) * (0.5 * 800 - 0.5);
			screenPointLeftTop.y = ( 600 - 1 ) - ( screenPointLeftTop.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			screenPointRightBottom.x = (screenPointRightBottom.x + 1) * (0.5 * 800 - 0.5);
			screenPointRightBottom.y = ( 600 - 1 ) - ( screenPointRightBottom.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			screenPointRightTop.x = (screenPointRightTop.x + 1) * (0.5 * 800 - 0.5);
			screenPointRightTop.y = ( 600 - 1 ) - ( screenPointRightTop.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			
			/*screenPointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, matrixProjection);
			screenPointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, matrixProjection );
			screenPointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, matrixProjection );
			screenPointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, matrixProjection);			
			/////////////////////////////////////////////////////////////////////////////////
			screenPointLeftTop.x = (-screenPointLeftTop.x / screenPointLeftTop.w)*this.size.x;
			screenPointLeftTop.y = (-screenPointLeftTop.y / screenPointLeftTop.w)*this.size.y;
			screenPointLeftTop.z = 0.0;
			//////////////////////////////////////////////////////////////////////////////////
			screenPointRightBottom.x = (-screenPointRightBottom.x / screenPointRightBottom.w)*this.size.x;
			screenPointRightBottom.y = (-screenPointRightBottom.y / screenPointRightBottom.w)*this.size.y;
			screenPointRightBottom.z = 0.0;
			///////////////////////////////////////////////////////////////////////////////////
			screenPointRightTop.x = (-screenPointRightTop.x / screenPointRightTop.w)*this.size.x;
			screenPointRightTop.y = (-screenPointRightTop.y / screenPointRightTop.w)*this.size.y;
			screenPointRightTop.z = 0.0;
			/////////////////////////////////////////////////////////////////////////////////
			screenPointLeftBottom.x = (-screenPointLeftBottom.x / screenPointLeftBottom.w)*this.size.x;
			screenPointLeftBottom.y = (-screenPointLeftBottom.y / screenPointLeftBottom.w)*this.size.y;
			screenPointLeftBottom.z = 0.0;	*/
		}
		
		private function rotateGlobal():void
		{
			this.matrixRotationX = mathUtils.matrixRotateX(this.globalRotation.x);
			this.matrixRotationY = mathUtils.matrixRotateY(this.globalRotation.y);
			this.matrixRotationZ = mathUtils.matrixRotateZ(0);
			
			this.matrixRotationX.m[11] = 1300;
			this.matrixRotationY.m[11] = 0;
			this.matrixRotationZ.m[11] = 1300;
			
			this.matrixRotationX.m[3] = -360;
			this.matrixRotationY.m[3] = 0;
			this.matrixRotationZ.m[3] = -360;
			
			pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationY);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, this.matrixRotationY);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationY);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationY);
			
			if (this.isMove == false)
			{
				this.matrixRotationX.m[7] = -340;
				this.matrixRotationY.m[7] = -340;
				this.matrixRotationZ.m[7] = -340;
			}
			else
			{
				this.matrixRotationX.m[7] = -340;
				this.matrixRotationY.m[7] = -340;
				this.matrixRotationZ.m[7] = -340;
			}
			
			pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationX);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop,this.matrixRotationX);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationX);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationX);
			
			
			pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationZ);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, this.matrixRotationZ);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationZ);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationZ);

		}
		
		private function translate():void
		{
			pointLeftTop.z += position.z;
			pointLeftTop.x += position.x;
			pointLeftTop.y += position.y;
			
			pointRightTop.z += position.z;
			pointRightTop.x += position.x;
			pointRightTop.y += position.y;
			
			pointLeftBottom.z += position.z;
			pointLeftBottom.x += position.x;
			pointLeftBottom.y += position.y;
			
			pointRightBottom.z += position.z;
			pointRightBottom.x += position.x;
			pointRightBottom.y += position.y;
			
			//pointLeftTop.z /= size.x;
			//pointRightTop.z /= size.x;
			//pointLeftBottom.z /= size.x;
			//pointRightBottom.z /= size.x;
		}
		
		private function rotateLocal():void 
		{
			this.matrixRotationX = mathUtils.matrixRotateX(this.localRotation.x);
			this.matrixRotationY = mathUtils.matrixRotateY(this.localRotation.y);
			this.matrixRotationZ = mathUtils.matrixRotateZ(this.localRotation.z);
			
			pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationX);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, this.matrixRotationX);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationX);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationX);
		
			/*pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationY);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, this.matrixRotationY);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationY);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationY);
			
			pointLeftBottom  = mathUtils.matrixMulVector(this.pointLeftBottom, this.matrixRotationZ);
			pointLeftTop     = mathUtils.matrixMulVector(this.pointLeftTop, this.matrixRotationZ);
			pointRightBottom = mathUtils.matrixMulVector(this.pointRightBottom, this.matrixRotationZ);
			pointRightTop    = mathUtils.matrixMulVector(this.pointRightTop, this.matrixRotationZ);*/
		}
	}
}