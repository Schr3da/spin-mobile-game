//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "OverViewController.h"
#import "Helper.h"
#import "OverviewContent.h"

@implementation OverViewController

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super init];
    if(self != nil){
        settings = NULL;
        datas = nil;
        settings = &PositionFactory::instance().getSettings();
        datas = [[Helper getOverviewContent]mutableCopy];
        self.view = [[[UIScrollView alloc]initWithFrame:frame]autorelease];
        UIScrollView *obj = ((UIScrollView *)self.view);
        obj.delegate = self;
        obj.showsHorizontalScrollIndicator = false;
        obj.showsVerticalScrollIndicator = false;
        obj.backgroundColor = [UIColor whiteColor];
        [self addContent];
    }
    return self;
}

-(void)addContent{
    if(settings == nil){
        NSLog(@"Error in addContentViewWithTitle settings are null");
        return;
    }
    int width = self.view.frame.size.width * 0.25;
    offset = CGPointMake(width*0.6, (self.view.frame.size.height - width - width*0.05)*0.5);
    for(OverviewContent *content in datas){
        [self addContentViewWithTitle:content.title Value:content.value size:width color:content.color imageName:content.imageName];
    }
}

-(void)addContentViewWithTitle:(NSString *)title Value:(NSString *)value size:(int)width color:(int)color imageName:(NSString *)imageName{
    UIColor *fontColor = [Helper getIUColorFromHex: settings->getGrayColor()];
    int insets = (int)(width *0.1);
    int ySpace = (int)width*0.05;
    
    UIButton *imageV = [[UIButton alloc]initWithFrame:CGRectMake(offset.x, offset.y, width, width)];
    imageV.imageEdgeInsets = UIEdgeInsetsMake(insets,insets,insets,insets);
    [imageV setImage:[UIImage imageNamed:imageName] forState:UIControlStateNormal];
    imageV.backgroundColor = [Helper getIUColorFromHex:color];
    imageV.userInteractionEnabled = false;
    [self.view addSubview:imageV];
    
    UILabel *valueL = [[UILabel alloc]initWithFrame:CGRectMake(offset.x, imageV.frame.origin.y + imageV.frame.size.height + ySpace*4, width, width*0.255)];
    valueL.text = value;
    valueL.textColor = fontColor;
    valueL.textAlignment = NSTextAlignmentCenter;
    valueL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:width*0.25];
    [self.view addSubview:valueL];
    
    UILabel *titleL = [[UILabel alloc]initWithFrame:CGRectMake(offset.x, valueL.frame.origin.y + valueL.frame.size.height + ySpace, width, width*0.16)];
    titleL.text = title;
    titleL.textColor = fontColor;
    titleL.textAlignment = NSTextAlignmentCenter;
    titleL.font = [UIFont fontWithName:@"HelveticaNeue" size:width*0.15];
    [self.view addSubview:titleL];
    
    offset.x += imageV.frame.size.width + width*0.6;
    ((UIScrollView *)self.view).contentSize = CGSizeMake(offset.x, offset.y);
    
    [imageV release];
    imageV = nil;
    [valueL release];
    valueL = nil;
    [titleL release];
    titleL = nil;
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

-(void)viewDidLoad{
    [super viewDidLoad];
}

-(BOOL)isNotNil{
    if(datas == nil){
        return false;
    }
    return true;
}

-(void)dealloc{
    UIView *view = self.view;
    [Helper releaseMutableContainer:&datas];
    [Helper removeSubviewsFromParent:&view];
    settings = NULL;
    [super dealloc];
}

@end
