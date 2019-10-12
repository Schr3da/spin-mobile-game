//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "SettingsView.h"
#import "LabelButton.h"
#import "GUI.h"
#import "Helper.h"
#import "SettingsViewController.h"

@implementation SettingsView

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super initWithFrame:frame];
    if(self != nil){
        backB = nil;
        [self addButtons];
    }
    return self;
}

-(void)addContentView{
    CGSize buttonSize = [Helper buttonSize];
    [Helper releaseViewControllerObject:&contentController];
    contentController = [[SettingsViewController alloc]initWithFrame:CGRectMake(0,
                                                                              0,
                                                                              self.frame.size.width,
                                                                              self.frame.size.height - buttonSize.height - [Helper screenBorderOffset]*2)];
    [self addSubview:contentController.view];
}

-(void)addButtons{
    CGSize buttonSize = [Helper buttonSize];
    buttonSize.width *= 2;
    [Helper releaseViewObject:&backB];
    backB = [[LabelButton alloc]initWithFrame:CGRectMake((self.frame.size.width - buttonSize.width)*0.5 ,
                                                         self.frame.size.height- buttonSize.height - [Helper screenBorderOffset],
                                                         buttonSize.width,
                                                         buttonSize.height)];
    
    [backB addLabelWithTitle:[Helper backText] andImage:[UIImage imageNamed:@"backIcon"]];
    [backB addTarget:self action:@selector(backToMenu:) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:backB];
}

-(void)backToMenu:(id)sender{
    Settings &settings = PositionFactory::instance().getSettings();
    settings.writeChangesToFile();
    [((GUI *)self.superview) hideCurrentView:[((LabelButton *)sender) getTitle]];
}


-(void)dealloc{
    [backB removeTarget:self action:@selector(backToMenu:) forControlEvents:UIControlEventTouchUpInside];
    [Helper releaseViewControllerObject:&contentController];
    [Helper releaseViewObject:&backB];
    [super dealloc];
}

@end
