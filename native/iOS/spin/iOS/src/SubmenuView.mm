//
//  SubmenuView.m
//  spin
//
//  Created by schr3da on 10/07/15.
//
//

#import "SubmenuView.h"
#import "Helper.h"
#import "GUI.h"

@implementation SubmenuView

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super initWithFrame:frame];
    if(self != nil){
        self.backgroundColor = [UIColor clearColor];
        [self addBackgroundView];
        [self addTextFields];
        [self addButtons];
    }
    return self;
}

-(void)addBackgroundView{
    
    [Helper releaseViewObject:&backgroundV];
    backgroundV = [[UIView alloc]initWithFrame:CGRectMake(self.frame.origin.x,
                                                             [Helper screenBorderOffset] + [Helper buttonSize].height,
                                                             self.frame.size.width,
                                                             self.frame.size.height - [Helper screenBorderOffset] - [Helper buttonSize].height)];
    backgroundV.alpha = 0.95f;
    backgroundV.backgroundColor = [UIColor whiteColor];
    [self addSubview:backgroundV];
}

-(void)addTextFields{
    
    [Helper releaseViewObject:&headerL];
    headerL = [[UILabel alloc]initWithFrame:CGRectMake((self.frame.size.width - self.frame.size.width *0.9)*0.5,
                                                       self.frame.size.height *0.65,
                                                       self.frame.size.width *0.9,
                                                       self.frame.size.width *0.08)];
    
    headerL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: headerL.frame.size.height];
    headerL.textColor = [Helper getGrayColor];
    headerL.textAlignment = NSTextAlignmentCenter;
    headerL.text = [Helper actionMenuTitle];
    [self addSubview:headerL];
    
    [Helper releaseViewObject:&textL];
    textL = [[UILabel alloc]initWithFrame:CGRectMake((self.frame.size.width - self.frame.size.width *0.9)*0.5,
                                                       headerL.frame.origin.y + headerL.frame.size.height*1.5,
                                                       self.frame.size.width *0.9,
                                                       self.frame.size.width *0.12)];
    textL.numberOfLines = 2;
    textL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size: textL.frame.size.height*0.4];
    textL.textColor = [Helper getGrayColor];
    textL.textAlignment = NSTextAlignmentCenter;
    textL.text = [Helper actionMenuText];
    [self addSubview:textL];
}

-(void)addButtons{
    CGPoint offset = CGPointMake(0, 0);
    CGSize buttonSize = [Helper buttonSize];
    int seperator = [Helper seperator];
    offset.x += (int) (self.frame.size.width - buttonSize.width * 3 - seperator * 3);
    int yPos = self.frame.size.height - buttonSize.height - [Helper screenBorderOffset];

    [self addNewLabelButton  :&menuB frame:CGRectMake(offset.x , yPos, buttonSize.width, buttonSize.height)
                    imageFile:@"backIcon"
                        title:[Helper backText]];
    
    offset.x += menuB.frame.size.width + seperator;
    
    [self addNewLabelButton  :&retryB frame:CGRectMake(offset.x , yPos, buttonSize.width, buttonSize.height)
                    imageFile:@"retryIcon"
                        title:[Helper restartText]];

    offset.x += retryB.frame.size.width + seperator;
    
    [self addNewLabelButton  :&continueB frame:CGRectMake(offset.x , yPos, buttonSize.width, buttonSize.height)
                    imageFile:@"continueIcon"
                        title:[Helper continueText]];
}

-(void)addNewLabelButton:(LabelButton **)button frame:(CGRect)frame imageFile:(NSString *)filename title:(NSString *)title{
    
    LabelButton *object = *button;
    [Helper releaseViewObject:&object];
    object = [[LabelButton alloc]initWithFrame:frame];
    [object addLabelWithTitle:title andImage:[UIImage imageNamed:filename]];
    [self addSubview:object];
    [object addTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    object.hidden = false;
    object.userInteractionEnabled = true;
    *button = object;
}

-(UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event{
    UIView *view = [super hitTest:point withEvent:event];
    if(view == self){
        return nil;
    }
    return view;
}

-(void)action:(id)sender{
    
    GUI *parentV = ((GUI*)self.superview);
    NSString *bText = [((LabelButton *)sender) getTitle];
    if([bText isEqualToString:[Helper restartText]]){
        [parentV hideCurrentView:[Helper retryText]];
    } else if([bText isEqualToString:[Helper backText]]) {
        [parentV hideCurrentView:bText];
    }
    [parentV interactWithSubmenu];
}

-(void)dealloc{
    
    [menuB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [retryB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    [continueB removeTarget:self action:@selector(action:) forControlEvents:UIControlEventTouchUpInside];
    
    [Helper releaseViewObject:&headerL];
    [Helper releaseViewObject:&textL];
    [Helper releaseViewObject:&backgroundV];
    [Helper releaseViewObject:&menuB];
    [Helper releaseViewObject:&retryB];
    [Helper releaseViewObject:&continueB];
    [super dealloc];
}

@end