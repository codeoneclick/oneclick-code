package 
{
	import flash.display.Sprite;
    import flash.events.Event;
	import flash.geom.Point;
    import flash.text.TextField;
    import flash.text.TextFieldAutoSize;
    import flash.utils.getTimer;
	/**
	 * ...
	 * @author OneClick
	 */

    public class FPSCounter extends Sprite
	{
        private var m_LastTime:uint = getTimer();
        private var m_TickCount:uint = 0;
        private var m_Text:TextField;

        public function FPSCounter(Position:Point, Color:uint=0xffffff, FillBackground:Boolean=false, BackgroundColor:uint=0x000000) {
            x = Position.x;
            y = Position.y;
            m_Text = new TextField();
            m_Text.textColor = Color;
            m_Text.text = "... fps";
            m_Text.selectable = false;
            m_Text.background = FillBackground;
            m_Text.backgroundColor = BackgroundColor;
            m_Text.autoSize = TextFieldAutoSize.LEFT;
            addChild(m_Text);
            width = m_Text.textWidth;
            height = m_Text.textHeight;
            addEventListener(Event.ENTER_FRAME, OnTick);
        }

        public function OnTick(event:Event):void {
            m_TickCount++;
            var CurrentTime:uint = getTimer();
            var DeltaTime:uint = CurrentTime - m_LastTime;
            if (DeltaTime >= 1000) {
                var Fps:Number = m_TickCount / DeltaTime * 1000;
                m_Text.text = Fps.toFixed(1) + " fps";
                m_TickCount = 0;
                m_LastTime = CurrentTime;
            }
        }
    }
}
