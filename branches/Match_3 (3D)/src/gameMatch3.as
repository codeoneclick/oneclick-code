package 
{
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.events.TimerEvent;
	import flash.geom.Rectangle;
	import flash.utils.Timer;
	import flash.geom.Point;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.system.Capabilities;
	import flash.display.StageScaleMode;

	/**
	 * Игра The Match 3
	 * @author PsyTech
	 */
	public class  gameMatch3 extends Sprite 
	{
		public  var matrixProjection        :matrix; 			// Матрица проецирования из 3D в Screen Space координаты.
		public  var planes                  :Array;  			// Масив представляющий игровое поле.
		public  var effectTimer             :Timer;  			// Таймер для визуализации эффекта при сложеных в ряд фишках.
		private var removeItemsList         :Array;  			// Список фишек на удаление.       
		private var removeItemsListLength   :int;	 			// Количество фишек для удаления.
		private var isImagesLoad            :Array;  			// Флаги для уведомления загрузки контента.
		private var pathList                :Array;  			// Список координат полученных при поиске пути.
		private var pathLength              :int = 0;			// Длина пути.
		private var globalRotation          :vector;    		// Глобальный поворот игрового поля в 3D.
		public  var loader                  :ContentLoader; 	// Загрузчик контента.
		public  var isPathReady             :Boolean = false;	// Флаг готовности пути.
		public  var nAngle					:Number = 0.0;		// Угол наклона игрового поля в 3D.
		private var pathIndexList			:Array;				// Список индексов плейнов игрового поля, для текущего пути.
		private var lastPathIndex           :int = -1; 			// Последний индекс, для визуализации перехода фишки из одной позиции в другую.
		public  var itemPickIndex           :int = -1;			// Индекс выбранной фишки.
		public  var panelPickIndex			:int = -1;			// Индекс выбранного плейна на игровом поле.
		private var endPanelIndex           :int = -1;			// Индекс конечной точки пути, для помечания этой точки как непроходимой.
		private var startPanelType          :int = 0;			// Индекс начальной точки пути, для помечания этой точки как проходимой.
		private var isMatch                 :Boolean = false;   // Флаг уведомления о успешном либо неуспешном МАТЧЕ.
		private var sizePanel               :int = 144;         // Размер игрового поля.
		private var sizeLine                :int = 12;			// Длина/Ширина игрового поля.
		public  var skinIndex				:int = 0;			// Индекс скина.
		
		public function gameMatch3():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			this.stage.frameRate = 100;
			this.stage.scaleMode = StageScaleMode.NO_SCALE;
			this.stage.addEventListener(Event.ENTER_FRAME, update);
			
			this.effectTimer = new Timer(25, 20);
			this.effectTimer.addEventListener(TimerEvent.TIMER, onEffectUse);
			this.effectTimer.addEventListener(TimerEvent.TIMER_COMPLETE, onEffectEnd);
			
			this.isImagesLoad = new Array();
			this.isImagesLoad[0] = false;
			this.isImagesLoad[1] = false;
			
			this.planes   = new Array(sizePanel);
			this.pathList = new Array();
			this.pathIndexList = new Array();
			
			matrixProjection = mathUtils.createMatrixProjection(0.1, 1000, 45,stage.width/stage.height);
			
			this.globalRotation = new vector();
			
			var i:int;
			var j:int;
			var index:int = 0;
			for (i = 0; i < this.sizeLine; i++)
			{
				for (j = 0; j < this.sizeLine; j++)
				{
					this.planes[index] = new mesh(this);
					this.planes[index].createIntersect();
					this.planes[index].value = -1;
					this.planes[index].index = index;
					this.planes[index].indexX = i;
					this.planes[index].indexY = j;
					this.addChild(this.planes[index].nonePlane);
					this.addChild(this.planes[index].itemPlane);
					index++;
				}
			}
			
			loader = new ContentLoader(this);
			loader.Path = "Content/";
			loader.Load("background");
			
			this.loader.imagesPath = "Content/";
			//////////////////////////////////////////////////
			this.loader.LoadImage("smileMainPanel");				//Имейдж для обычного поля.
			this.loader.LoadImage("smilePickPanel");				//Имейдж для пикнутого поля.
			this.loader.LoadImage("smileMatchPanel");				//Имейдж для пикнутого поля.
			this.loader.LoadImage("skullMainPanel");				//Имейдж для обычного поля.
			this.loader.LoadImage("skullPickPanel");				//Имейдж для пикнутого поля.
			this.loader.LoadImage("skullMatchPanel");				//Имейдж для пикнутого поля.
			//////////////////////////////////////////////////
			this.loader.LoadImage("smileMovePanel");				//Имейдж отображающий фишку при перемещении.
			this.loader.LoadImage("skullMovePanel");				//Имейдж отображающий фишку при перемещении.
			/////////////////////////////////////////////////
			this.loader.LoadImage("smile01MainPanel");				//Красная обыная фишка.
			this.loader.LoadImage("smile02MainPanel");			//Зеленная обыная фишка.
			this.loader.LoadImage("smile03MainPanel");				//Синяя обыная фишка.
			this.loader.LoadImage("skull01MainPanel");				//Красная обыная фишка.
			this.loader.LoadImage("skull02MainPanel");			//Зеленная обыная фишка.
			this.loader.LoadImage("skull03MainPanel");				//Синяя обыная фишка.
			//////////////////////////////////////////////////
			this.loader.LoadImage("smile01PickPanel");				//Красная пикнутая фишка.
			this.loader.LoadImage("smile02PickPanel");			//Зеленная пикнутая фишка.
			this.loader.LoadImage("smile03PickPanel");				//Синяя пикнутая фишка.
			this.loader.LoadImage("skull01PickPanel");				//Красная пикнутая фишка.
			this.loader.LoadImage("skull02PickPanel");			//Зеленная пикнутая фишка.
			this.loader.LoadImage("skull03PickPanel");				//Синяя пикнутая фишка.
			/////////////////////////////////////////////////
			this.loader.LoadImage("smile01HalfPanel");			//Красная половинка фишки.
			this.loader.LoadImage("smile02HalfPanel");		//Синяя половинка фишки.
			this.loader.LoadImage("smile03HalfPanel");			//Зеленная половинка фишки.
			this.loader.LoadImage("skull01HalfPanel");			//Красная половинка фишки.
			this.loader.LoadImage("skull02HalfPanel");		//Синяя половинка фишки.
			this.loader.LoadImage("skull03HalfPanel");			//Зеленная половинка фишки.
		}	

		public function initPlaneImages():void
		{
			var i:int;
			for (i = 0; i < sizePanel; i++){
				this.planes[i].contentLoader = this.loader;
				this.planes[i].setSkin("smile");
				//this.planes[i].setImageSourcePick(this.loader.imagesManager["nonePickPanel"]);
				//this.planes[i].setMoveImage(this.loader.imagesManager["moveMainPanel"]);
				//////////////////////////////////////////////////////////////////////////////////////////////
				//this.planes[i].setItemImage(this.loader.imagesManager["redMainPanel"],"redMainPanel");
				//this.planes[i].setItemImage(this.loader.imagesManager["greenMainPanel"],"greenMainPanel");
				//this.planes[i].setItemImage(this.loader.imagesManager["blueMainPanel"], "blueMainPanel");
				//////////////////////////////////////////////////////////////////////////////////////////////
				//this.planes[i].setItemImagePick(this.loader.imagesManager["redPickPanel"],"redPickPanel");
				//this.planes[i].setItemImagePick(this.loader.imagesManager["greenPickPanel"],"greenPickPanel");
				//this.planes[i].setItemImagePick(this.loader.imagesManager["bluePickPanel"], "bluePickPanel");
				//////////////////////////////////////////////////////////////////////////////////////////////
				//this.planes[i].setHalfItemImage(this.loader.imagesManager["redMainHalfPanel"],"redMainHalfPanel");
				//this.planes[i].setHalfItemImage(this.loader.imagesManager["greenMainHalfPanel"],"greenMainHalfPanel");
				//this.planes[i].setHalfItemImage(this.loader.imagesManager["blueMainHalfPanel"], "blueMainHalfPanel");
			}
			this.createHalfItems();
			this.createItems();
			this.createMatchPanels();
			this.isImagesLoad[1] = true;
			this.isImagesLoad[0] = true;
			this.updateRender();
		}
		
		private function random(min:int, max:int):int
		{
			var range:int = (max - min) + 1;
			return min + range * Math.random() / 2;
		}
		
		public function createMatchPanels():void
		{
			var randomIndex:int = 15;
			for (var i:int = 0; i < randomIndex; i++)
			{
				var index:int = Math.random() * (sizePanel - 1);
				
				if (this.planes[index].isMatchPanel != true)
				{
					this.planes[index].isMatchPanel = true;
				}
				else
				{
					randomIndex++;
				}
				
				if (randomIndex > 1024) return;
			}
		}

		public function createHalfItems():void
		{
			var randomIndex:int = 15;
			for (var i:int = 0; i < randomIndex; i++)
			{
				var index:int = Math.random() * (sizePanel - 1);
				
				if (this.planes[index].value != -2)
				{
					var itemType:int = Math.random() * 3 + 3;
					this.planes[index].panelType = itemType;
					this.planes[index].value = -1;
				}
				else
				{
					randomIndex++;
				}
				
				if (randomIndex > 1024) return;
			}
		}
		
		private function createItems():void
		{
			var i:int;
			for (i = 0; i < sizePanel; i++)
			{
				if (this.planes[i].panelType > 2)
				{
					this.planes[i].itemType = this.planes[i].panelType - 2;
					this.planes[i].panelType = 0;
					this.planes[i].value = -2;
				}
			}
		}
		
		public function initImages():void
		{
			trace(loader.sources_manager["background"]);
			this.addChildAt(loader.sources_manager["background"].background, 0);
			this.addChildAt(loader.sources_manager["background"].backgroundSkull, 0);
			loader.sources_manager["background"].backgroundSkull.visible = false;
			this.addChild(loader.sources_manager["background"].moveLeft);
			this.addChild(loader.sources_manager["background"].moveRight);
			this.addChild(loader.sources_manager["background"].moveUp);
			this.addChild(loader.sources_manager["background"].moveDown);
			this.addChild(loader.sources_manager["background"].select2D);
			this.addChild(loader.sources_manager["background"].select3D);
			this.addChild(loader.sources_manager["background"].selectSkin);
			this.addChild(loader.sources_manager["background"].simpleProgress);
			loader.sources_manager["background"].simpleProgress.gotoAndStop(1);
			this.addChild(loader.sources_manager["background"].mainProgress);
			loader.sources_manager["background"].mainProgress.gotoAndStop(1);
			loader.sources_manager["background"].moveLeft.addEventListener(MouseEvent.MOUSE_DOWN, onLeftClick);
			loader.sources_manager["background"].moveRight.addEventListener(MouseEvent.MOUSE_DOWN, onRightClick);
			loader.sources_manager["background"].moveUp.addEventListener(MouseEvent.MOUSE_DOWN, onUpClick);
			loader.sources_manager["background"].moveDown.addEventListener(MouseEvent.MOUSE_DOWN, onDownClick);
			loader.sources_manager["background"].select2D.addEventListener(MouseEvent.MOUSE_DOWN, on2DClick);
			loader.sources_manager["background"].select3D.addEventListener(MouseEvent.MOUSE_DOWN, on3DClick);
			loader.sources_manager["background"].selectSkin.addEventListener(MouseEvent.MOUSE_DOWN, onSkinClick);
		}
		
		public function findPath():void
		{
			if (this.planes[this.panelPickIndex ].value == -2) return;
			isPathReady = false;
			if ((this.panelPickIndex == -1) || (this.itemPickIndex == -1)) return;
			var i:int = 0;
			var j:int = 0;
			var k:int = 0;
			for (i = 0; i < sizePanel; i++)
				if(i != this.itemPickIndex && this.planes[i].value != -2)
					this.planes[i].value = -1;

			this.planes[this.itemPickIndex].value = 0;
			var currentValue:int = 0;
			var iteration:int = 0;

			var isPathFind:Boolean = false;

			for (i = 0; i < sizePanel; i++)
			{
				if (isPathFind == true) break;
				for (j = 0; j < sizePanel; j++)
				{
					if (this.planes[j].value != -1 && this.planes[j].value != -2)
					{
						for (k = 0; k < sizePanel; k++)
						{
							iteration++;
							if (iteration > 65536*2) isPathFind = true;
							if ((this.planes[k].indexX == (this.planes[j].indexX + 1)) && (this.planes[k].indexY == this.planes[j].indexY))
							{
								if (this.planes[k].value == -1)
								{
									this.planes[k].value = this.planes[j].value + 1;
									if (k == this.panelPickIndex)
									{
										isPathFind = true;
										break;
									}
								}
							}	
							if ((this.planes[k].indexX == (this.planes[j].indexX - 1)) && (this.planes[k].indexY == this.planes[j].indexY))
							{
								if (this.planes[k].value == -1)
								{
									this.planes[k].value = this.planes[j].value + 1;
									if (k == this.panelPickIndex)
									{
										isPathFind = true;
										break;
									}
								}
							}
							if ((this.planes[k].indexY == (this.planes[j].indexY + 1)) && (this.planes[k].indexX == this.planes[j].indexX))
							{
								if (this.planes[k].value == -1)
								{
									this.planes[k].value = this.planes[j].value +1;
									if (k == this.panelPickIndex)
									{
										isPathFind = true;
										break;
									}
								}
							}
							if ((this.planes[k].indexY == (this.planes[j].indexY - 1)) && (this.planes[k].indexX == this.planes[j].indexX))
							{
								if (this.planes[k].value == -1)
								{
									this.planes[k].value = this.planes[j].value +1;
									if (k == this.panelPickIndex)
									{
										isPathFind = true;
										break;
									}
								}
							}
						}
					}
				}
			}
				
			trace(iteration);
			this.pathLength = 0;
			var min:int = this.planes[this.panelPickIndex].value;
			if (isPathFind == false || min < 0)
			{
				this.itemPickIndex = -1;
				this.panelPickIndex = -1;
				return; 
			}
			this.pathList[this.pathLength] = new Point(this.planes[this.panelPickIndex].position.x, this.planes[this.panelPickIndex].position.z);
			this.pathIndexList[this.pathLength] = this.panelPickIndex;
			this.pathLength++;
			var selectNextIndex:int = 0;
			var selectCurrentIndex:int = this.panelPickIndex;
			for (j = 0; j < this.planes[this.panelPickIndex].value; j++ )
				{
						if ((selectCurrentIndex + 1) < sizePanel)
							if (this.planes[selectCurrentIndex + 1].value < min && this.planes[selectCurrentIndex + 1].value > -1)
							{
								min = this.planes[selectCurrentIndex + 1].value;
								selectNextIndex = selectCurrentIndex + 1;
							}
						if ((selectCurrentIndex - 1) > -1)
							if (this.planes[selectCurrentIndex - 1].value < min && this.planes[selectCurrentIndex - 1].value > -1)
							{
								min = this.planes[selectCurrentIndex - 1].value;
								selectNextIndex = selectCurrentIndex - 1;
							}
						if ((selectCurrentIndex + sizeLine) < sizePanel)
							if (this.planes[selectCurrentIndex + sizeLine].value < min && this.planes[selectCurrentIndex + sizeLine].value > -1)
							{
								min = this.planes[selectCurrentIndex + sizeLine].value;
								selectNextIndex = selectCurrentIndex + sizeLine;
							}
						if ((selectCurrentIndex - sizeLine) > 0)
							if (this.planes[selectCurrentIndex - sizeLine].value < min && this.planes[selectCurrentIndex - sizeLine].value > -1)
							{
								min = this.planes[selectCurrentIndex - sizeLine].value;
								selectNextIndex = selectCurrentIndex - sizeLine;
							}
						selectCurrentIndex = selectNextIndex;
						this.pathList[this.pathLength] = new Point(this.planes[selectCurrentIndex].position.x, this.planes[selectCurrentIndex].position.z);
						this.pathIndexList[this.pathLength] = selectCurrentIndex;
						this.pathLength++;
					}
			this.startPanelType = this.planes[this.itemPickIndex].itemType;
			this.planes[this.itemPickIndex].itemType = 0;
			this.planes[this.itemPickIndex].value = -1;
			this.planes[this.itemPickIndex].isClick = false;
			this.endPanelIndex = this.panelPickIndex;
			this.itemPickIndex = -1;
			this.panelPickIndex = -1;
			isPathReady = true;
		
		}
		
		public function normalize(vector_in:vector):void
		{
			var vector_length:Number =  new Number(Math.sqrt(vector_in.x*vector_in.x + vector_in.y*vector_in.y +vector_in.z*vector_in.z));
			vector_in.x /= vector_length;
			vector_in.y /= vector_length;
			vector_in.z /= vector_length;
		}

		public function dotProduct(vector_in_1:vector,vector_in_2:vector):Number
		{
			return (vector_in_1.x * vector_in_2.x + vector_in_1.y * vector_in_2.y + vector_in_1.z * vector_in_2.z);
		}
		
		public function crossProduct(vector_out:vector,vector_in_1:vector,vector_in_2:vector):void
		{
			vector_out.x = vector_in_1.y*vector_in_2.z - vector_in_1.z*vector_in_2.y;
			vector_out.y = vector_in_1.z*vector_in_2.x - vector_in_1.x*vector_in_2.z;
			vector_out.z = vector_in_1.x*vector_in_2.y - vector_in_1.y*vector_in_2.x;
		}
		
		private function onLeftClick(event:MouseEvent):void
		{
			this.globalRotation.y += 0.05;
			var i:int;
			for (i = 0; i < sizePanel;i++)
			this.planes[i].itemPlane.visible = false;
			this.updateRender();
		}
		
		private function onSkinClick(event:MouseEvent):void
		{
			var i:int;
			if (this.skinIndex == 0)
			{
				for (i = 0; i < sizePanel; i++)
				{
					loader.sources_manager["background"].background.visible = false;
					loader.sources_manager["background"].backgroundSkull.visible = true;
					this.planes[i].setSkin("skull");
					this.planes[i].draw();
					this.skinIndex = 1;
				}
			}
			else
			{
				for (i = 0; i < sizePanel; i++)
				{
					loader.sources_manager["background"].background.visible = true;
					loader.sources_manager["background"].backgroundSkull.visible = false;
					this.planes[i].setSkin("smile");
					this.planes[i].draw();
					this.skinIndex = 1;
				}
				this.skinIndex = 0;
			}
		}
		
		
		private function onUpClick(event:MouseEvent):void
		{
			if(this.nAngle > 0.3925/2){
				this.nAngle -= 0.1;
				this.updateRender();
			}
		}
		
		private function onDownClick(event:MouseEvent):void
		{
			if (this.nAngle < 1.57){
				this.nAngle += 0.1;
				this.updateRender();
			}
		}
		
		private function onRightClick(event:MouseEvent):void
		{
			this.globalRotation.y -= 0.05;
			this.updateRender();
		}
		
		private function on2DClick(event:MouseEvent):void
		{
			this.nAngle = 1.57;
			this.globalRotation.y = 0;
			this.updateRender();
		}
		
		private function on3DClick(event:MouseEvent):void
		{
			this.nAngle = 0.3925;
			this.globalRotation.y = 0;
			this.updateRender();
		}
		
		private function updateRender():void
		{
			if (!isImagesLoad[0] && !isImagesLoad[1])
				return;
		
			var i:int;
			var index:int = 0;
			for (i = -sizeLine/2; i < sizeLine/2; i++){
				var j:int;
				for (j = -sizeLine/2; j < sizeLine/2; j++)
				{
					this.planes[index].position.y = 0;
					this.planes[index].position.x = 85 * i+32;
					this.planes[index].position.z = 85 * j+32;
					this.planes[index].localRotation.x = 3.14 / 2;
					this.planes[index].globalRotation.x = nAngle;
					this.planes[index].globalRotation.y = this.globalRotation.y;
					this.planes[index].update();
					this.planes[index].rasterize(this.matrixProjection);
					this.planes[index].draw();
					index++;
				}
			}
		}
		
		private function removeItem():void
		{
			
			removeItemsList = new Array();
			removeItemsListLength = 0;
			this.isMatch = false;
			
			var i:int;
			var j:int;
			var k:int;
			var lastTypeValue:int = -5;
			var sum:int = 0;
			
			for (i = 0; i < this.sizeLine; i++)
			{
				lastTypeValue = -5;
				sum = 0;
				for (j = 0; j < sizeLine; j++)
				{
					if (this.planes[i + j * sizeLine].itemType != 0)
					{
						if (this.planes[i + j * sizeLine].itemType == lastTypeValue)
						{
							sum++;
						}
						else
						{
							sum = 0;
						}
					}
					else
					{
						sum = 0;
					}
					
					lastTypeValue = this.planes[i + j * sizeLine].itemType;

					if (sum > 1)
					{
						for (k = 0; k < sum + 1; k++)
						{
							removeItemsList[removeItemsListLength] = (i + (j-k) * sizeLine);
							removeItemsListLength++;
							this.isMatch = true;
						}
					}
				}
			}
			
			
			for (j = 0; j < sizeLine; j++)
			{
				lastTypeValue = -5;
				sum = 0;
				for (i = 0; i < sizeLine; i++)
				{
					if (this.planes[i + j * sizeLine].itemType != 0)
					{
						if (this.planes[i + j * sizeLine].itemType == lastTypeValue)
						{
							sum++;
						}
						else
						{
							sum = 0;
						}
					}
					else
					{
						sum = 0;
					}
					
					lastTypeValue = this.planes[i + j * sizeLine].itemType;

					if (sum > 1)
					{
						for (k = 0; k < sum + 1; k++)
						{
							removeItemsList[removeItemsListLength] = ((i - k) + j* sizeLine);
							removeItemsListLength++;
							this.isMatch = true;
						}
					}
				}
			}
	
			if (removeItemsListLength > 0)
				this.effectTimer.start();
		}
		
		private function onEffectUse(event:TimerEvent):void
		{
			var i:int;
			for (i = 0; i < removeItemsListLength; i++)
			{
				this.planes[removeItemsList[i]].position.y+=5;
				this.planes[removeItemsList[i]].update();
				this.planes[removeItemsList[i]].rasterize(this.matrixProjection);
				this.planes[removeItemsList[i]].draw();
			}
		}
		
		public function clearClickIntersection():void
		{
			if (this.itemPickIndex >= 0)
				this.planes[this.itemPickIndex].isClick = false;
		}
		
		private function onEffectEnd(event:TimerEvent):void
		{
			var i:int;
			for (i = 0; i < removeItemsListLength; i++)
			{
				this.planes[removeItemsList[i]].value = -1;
				if (this.planes[removeItemsList[i]].isMatchPanel == true)
				{
					loader.sources_manager["background"].mainProgress.gotoAndStop(loader.sources_manager["background"].mainProgress.currentFrame + 7);
				}
				
				if (this.planes[removeItemsList[i]].itemType != 0)
				{
					loader.sources_manager["background"].simpleProgress.gotoAndStop(loader.sources_manager["background"].simpleProgress.currentFrame + 1);
				}
					
				this.planes[removeItemsList[i]].isMatchPanel = false;
				this.planes[removeItemsList[i]].itemType = 0;
				this.planes[removeItemsList[i]].position.y = 0;
				this.planes[removeItemsList[i]].update();
				this.planes[removeItemsList[i]].rasterize(this.matrixProjection);
				this.planes[removeItemsList[i]].draw();
			}
			this.effectTimer.reset();
		}
		
		private function update(event:Event):void
		{
			if (!isImagesLoad[0] && !isImagesLoad[1])
				return;
		
			var i:int;
			for (i = 0; i < sizePanel; i++)
				this.planes[i].updateIntersect();
			
			if (this.pathLength != 0 && isPathReady == true)
			{
				if (this.lastPathIndex != -1)
				{
				  this.planes[this.lastPathIndex].setNonePanel();
				}
				this.planes[this.pathIndexList[this.pathLength - 1]].setMovePanel();
				this.lastPathIndex = this.pathIndexList[this.pathLength - 1];
				this.pathLength--;
				if (pathLength == 0)
				{
					isPathReady = false;
					this.planes[this.endPanelIndex].itemType = this.startPanelType;
					this.planes[this.endPanelIndex].panelType = 0;
					this.planes[this.endPanelIndex].value = -2;
					this.removeItem();
					if (this.isMatch == false)
					{
						this.createItems();
						this.createHalfItems();
						this.removeItem();
					}
				}
			}
		}
	}
}