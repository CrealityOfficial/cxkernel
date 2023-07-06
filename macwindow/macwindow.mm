#include "macwindow.h"

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
@end

@implementation WindowDelegate

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    //重构退出全屏操作
    NSLog(@"windowDidExitFullScreen");
    // NSWindow *window = notification.object;
    // window.styleMask |= NSFullSizeContentViewWindowMask;
      NSLog(@"windowDidExitFullScreen --%@", notification);
   NSWindow *window = notification.object;
   window.styleMask |= NSFullSizeContentViewWindowMask;
    // NSButton *button = [window standardWindowButton:NSWindowZoomButton];
    // button.hidden = NO;
    // button.frame = NSMakeRect(button.frame.origin.x, 60, button.frame.size.width, button.frame.size.height);
    // [(NSView *)window.contentView addSubview:button];
    // NSLog(@"button.frame.size.height --%@", button.frame.size.height);

    // NSButton *button1 = [window standardWindowButton:NSWindowCloseButton];
    // button1.hidden = NO;
    // button1.frame = NSMakeRect(button1.frame.origin.x, 60, button1.frame.size.width, button1.frame.size.height);
    // [(NSView *)window.contentView  addSubview:button1];


    // NSButton *button2 = [window standardWindowButton:NSWindowMiniaturizeButton];
    // button2.hidden = NO;
    // button2.frame = NSMakeRect(button2.frame.origin.x, 60, button2.frame.size.width, button2.frame.size.height);
    // [(NSView *)window.contentView addSubview:button2];
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    //重构退出
    NSLog(@"windowShouldClose");
    exit(0);
    return YES;
}
@end

MacWindow::MacWindow(QWindow *window, QWindow *accessoryWindow)
:m_window(window)
,m_accessoryWindow(accessoryWindow)
{

}
MacWindow::MacWindow()
{


}
void MacWindow::setContentWindow(QWindow *contentWindow)
{
    m_window = contentWindow;
//    scheduleRecreateNSWindow();
}

void MacWindow::setLeftAcccessoryWindow(QWindow *leftAccessoryWindow)
{
    m_accessoryWindow = leftAccessoryWindow;
    scheduleRecreateNSWindow();
}

void MacWindow::setRightAcccessoryWindow(QWindow *rightAccessoryWindow)
{
    m_rightAccessoryWindow = rightAccessoryWindow;
    scheduleRecreateNSWindow();
}

void MacWindow::createNSWindow()
{
    qDebug() << "createNSWindow";

#if 0
    if (m_nsWindow)
        return;
    auto styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                     NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable | NSFullSizeContentViewWindowMask;

    if (true)
        styleMask |= NSFullSizeContentViewWindowMask;

    NSRect frame = NSMakeRect(m_window->x(), m_window->y(), m_window->width(), m_window->height());
    m_nsWindow =
        [[NSWindow alloc] initWithContentRect:frame
                                    styleMask:styleMask
                                      backing:NSBackingStoreBuffered
                                        defer:NO];

    m_nsWindow.titleVisibility = m_titleVisibility ? NSWindowTitleVisible : NSWindowTitleHidden;
    m_nsWindow.title = m_titleText.toNSString();
    m_nsWindow.titlebarAppearsTransparent = true;
    m_nsWindow.movableByWindowBackground = true;
    if (m_toolbarEnabled) {
        NSToolbar *toolbar = [[NSToolbar alloc] initWithIdentifier:@"main"];
        toolbar.showsBaselineSeparator = false;
        m_nsWindow.toolbar = toolbar;
    }
    m_nsWindow.contentView = (__bridge NSView *)reinterpret_cast<void *>(m_window->winId());
#else
    if (m_nsWindow)
        return;

    NSView *view = (__bridge NSView *)reinterpret_cast<void *>(m_window->winId());
    NSWindow *window = [view window];
    window.delegate = [[WindowDelegate alloc] init];
    m_nsWindow = window;
    m_nsWindow.titleVisibility = m_titleVisibility ? NSWindowTitleVisible : NSWindowTitleHidden;
    m_nsWindow.titlebarAppearsTransparent = m_titlebarAppearsTransparent;
    m_nsWindow.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                         NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable | NSFullSizeContentViewWindowMask;
#endif

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
//    QTimer::singleShot(0, [this](){
//        recreateNSWindow();
//    });
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
//    scheduleRecreateNSWindow();
}

bool MacWindow::titlebarAppearsTransparent() const
{
    return m_titlebarAppearsTransparent;
}

void MacWindow::setToolbarEnabled(bool enable)
{
    if (m_toolbarEnabled == enable)
        return;

    m_toolbarEnabled = enable;
//    scheduleRecreateNSWindow();
}

bool MacWindow::toolbarEnabled() const
{
    return m_toolbarEnabled;
}

void MacWindow::setShowsBaselineSeparator(bool enable)
{
    if (m_showsBaselineSeparator == enable)
        return;

    m_showsBaselineSeparator = enable;
    scheduleRecreateNSWindow();
}

bool MacWindow::showsBaselineSeparator() const
{
    return m_showsBaselineSeparator;
}

void MacWindow::setTitleVisibility(bool enable)
{
    if (m_titleVisibility == enable)
        return;

    m_titleVisibility = enable;
//    if (m_nsWindow)
//        return;

//    NSView *view = (__bridge NSView *)reinterpret_cast<void *>(m_window->winId());
//    NSWindow *window = [view window];
//    window.delegate = [[WindowDelegate alloc] init];
//    m_nsWindow = window;
//    m_nsWindow.titleVisibility = m_titleVisibility ? NSWindowTitleVisible : NSWindowTitleHidden;
//    m_nsWindow.titlebarAppearsTransparent = YES;
//    m_nsWindow.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
//                         NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable | NSFullSizeContentViewWindowMask;
//    [m_nsWindow makeKeyAndOrderFront:nil];
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

