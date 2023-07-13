#include "macwindow.h"
#include "mycppobject.h"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

// An NSTitlebarAccessoryViewController that controls a programatically created view
@interface ProgramaticViewController : NSTitlebarAccessoryViewController
@end

@implementation ProgramaticViewController
- (id)initWithView: (NSView *)aView
{
    self = [self init];
    self.view = aView;
    return self;
}
@end


//[[NSNotificationCenter defaultCenter]addObserver:self selector@selector (willEnterFull)name:NSWindowWillEnterFullScreenNotification object:nil];

@interface WindowDelegate : NSObject <NSWindowDelegate>
@property (nonatomic, assign) float topY;
@property (nonatomic, assign) MyCppObject *wrapped;

@property (nonatomic,assign) void (^windowShouldClosecCallback)();
@end

@implementation WindowDelegate

- (void)exampleMethodWithString:(NSString *)str
{
    std::string cpp_str([str UTF8String],[str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);

    self.wrapped->ExampleMethod(cpp_str);
    NSLog(@"exampleMethodWithString");

}
- (void)useselfClose:(NSInteger) size
{
    self.wrapped->closeFunction();

}

- (id)init
{
    if(self =[super init])
    {
        //初始化对象
        self.wrapped = new MyCppObject();
    }
    return self;
}

- (void)dealloc
{
    delete self.wrapped;
    [super dealloc];
}

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    //重构退出全屏操作
    NSLog(@"windowDidExitFullScreen");
    // NSWindow *window = notification.object;
    // window.styleMask |= NSFullSizeContentViewWindowMask;
      NSLog(@"windowDidExitFullScreen --%@", notification);
   NSWindow *window = notification.object;

    // NSButton *button = [window standardWindowButton:NSWindowZoomButton];
    // button.hidden = NO;
    // button.frame = NSMakeRect(button.frame.origin.x, 0, button.frame.size.width, button.frame.size.height);
    // [(NSView *)window.contentView addSubview:button];
    // NSLog(@"button.frame.size.height --%@", button.frame.size.height);

    // NSButton *button1 = [window standardWindowButton:NSWindowCloseButton];
    // button1.hidden = NO;
    // button1.frame = NSMakeRect(button1.frame.origin.x, 0, button1.frame.size.width, button1.frame.size.height);
    // [(NSView *)window.contentView  addSubview:button1];


    // NSButton *button2 = [window standardWindowButton:NSWindowMiniaturizeButton];
    // button2.hidden = NO;
    // button2.frame = NSMakeRect(button2.frame.origin.x, 0, button2.frame.size.width, button2.frame.size.height);
    // [(NSView *)window.contentView addSubview:button2];

        // NSTitlebarAccessoryViewController *vc = [[NSTitlebarAccessoryViewController alloc] init];
        // vc.view = [[NSView alloc] initWithFrame:((NSView *)window.contentView).frame];
        // [window addTitlebarAccessoryViewController:vc];

        // NSButton *button = [window standardWindowButton:NSWindowZoomButton];
        // NSRect rect = button.frame;
        // rect.origin.y -= 10;
        // button.frame = rect;

     window.styleMask |= NSFullSizeContentViewWindowMask;
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    //重构退出
    NSLog(@"windowShouldClose");
    [self exampleMethodWithString:@"window close example"];

    [self useselfClose:0];
    if(self.windowShouldClosecCallback)
    {
        self.windowShouldClosecCallback();

    }
    return NO;
}

- (void)windowWillClose:(NSNotification *)notification
{
    //重构退出
    NSLog(@"windowWillClose");
  //  exit(0);
}
@end


MacWindow::MacWindow()
{


}
void MacWindow::setContentWindow(QWindow *contentWindow)
{
    m_window = contentWindow;
}

void MacWindow::createNSWindow()
{
    qDebug() << "createNSWindow";
    if (m_nsWindow)
        return;

    NSView *view = (__bridge NSView *)reinterpret_cast<void *>(m_window->winId());
    NSWindow *window = [view window];


    WindowDelegate *delegate = [[WindowDelegate alloc] init];
    delegate.topY = 10.0;
    m_macAppObject =  delegate.wrapped;

    [delegate exampleMethodWithString:@"hello"];

    delegate.windowShouldClosecCallback = ^(){

            //   destroyNSWindow();
             printf("windowShouldClosecCallback\n");
         };
    window.delegate = delegate;

    m_nsWindow = window;
    m_nsWindow.titleVisibility = m_titleVisibility ? NSWindowTitleVisible : NSWindowTitleHidden;
    m_nsWindow.titlebarAppearsTransparent = m_titlebarAppearsTransparent;
    m_nsWindow.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable| NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
                         | NSFullSizeContentViewWindowMask;


}

void MacWindow::destroyNSWindow()
{
     @autoreleasepool {
         [m_nsWindow close];
         m_nsWindow = nil;
     }
}

void MacWindow::recreateNSWindow()
{
    if (!m_nsWindow)
        return;

    destroyNSWindow();
    createNSWindow();

    if (m_visible)
        [m_nsWindow makeKeyAndOrderFront:nil];
}

void MacWindow::scheduleRecreateNSWindow()
{
}

void MacWindow::setFullSizeContentView(bool enable)
{
    if (m_fullSizeContentView == enable)
        return;
    m_fullSizeContentView = enable;
    scheduleRecreateNSWindow();
}

bool MacWindow::fullSizeContentView() const
{
    return m_fullSizeContentView;
}

void MacWindow::setTitlebarAppearsTransparent(bool enable)
{
    if (m_titlebarAppearsTransparent == enable)
        return;

    m_titlebarAppearsTransparent = enable ? YES : NO;
}

bool MacWindow::titlebarAppearsTransparent() const
{
    return m_titlebarAppearsTransparent;
}



void MacWindow::setTitleVisibility(bool enable)
{
    if (m_titleVisibility == enable)
        return;
    m_titleVisibility = enable;
}

bool MacWindow::titleVisibility() const
{
    return m_titleVisibility;
}

void MacWindow::setVisible(bool visible)
{
    qDebug() << "setVisible" << visible;
    m_visible = visible;
    if (visible) {
        createNSWindow();
        [m_nsWindow makeKeyAndOrderFront:nil];
    } else {

    }
}

void MacWindow::show()
{
    setVisible(true);
}
// void MacWindow::setMacObject(MyCppObject *cppObject)
// {
//     m_macAppObject = cppObject;
// }

MyCppObject *MacWindow::getMacAppObject()
{
    return m_macAppObject;
}
