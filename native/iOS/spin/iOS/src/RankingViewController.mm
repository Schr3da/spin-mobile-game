//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "RankingViewController.h"
#import "Helper.h"
#import "RankingContent.h"
#import "RankingCell.h"

@implementation RankingViewController

-(instancetype)initWithFrame:(CGRect)frame{
    
    self = [super init];
    if(self != nil){
        datas = nil;
        datas = [[Helper getRankingContent]mutableCopy];
        leadboardPosition = 0;
        self.view.frame = frame;
        settings = &PositionFactory::instance().getSettings();
        if(settings == NULL || datas == nil){
            NSLog(@"RankingViewController subview inital error");
            return self;
        }
        [self addContent];
    }
    return self;
}

-(void)addContent{
    int width = (int)(self.view.frame.size.width * 0.25);
    offset = CGPointMake((self.view.frame.size.width - datas.count * width - width*0.6) * 0.5, (self.view.frame.size.height - width)*0.5);
    for(RankingContent *obj in datas){
        if(obj != nil){
            if([obj.title isEqualToString:@"Leaderboard"]){
                [self requestLeaderboard];
            }
            [self addContentViewWithTitle:obj.title Value:obj.value size:width color:obj.color imageName:obj.imageName];
        }
    }
}

-(void)requestLeaderboard{
    if(settings->getHightscore() <= 0){
        return;
    }
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:[Helper leaderboardURL]]];
    request.HTTPMethod = @"POST";
    request.HTTPBody = [[NSString stringWithFormat:@"mobileRequest=true&highscore=%d", settings->getHightscore()]dataUsingEncoding:
                                                                                    NSASCIIStringEncoding allowLossyConversion:YES];
    [NSURLConnection connectionWithRequest:request delegate:self];
}

-(void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data{
    NSDictionary *json = [NSJSONSerialization JSONObjectWithData:data options:NSJSONWritingPrettyPrinted error:nil];
    if(json != nil){
        leadboardPosition = [[json objectForKey:@"position"] intValue];
    }
}

-(void)connectionDidFinishLoading:(NSURLConnection *)connection{
    if(leadboardPosition != 0){
        [self setLeaderboardValue:[NSString stringWithFormat:@"#%d", leadboardPosition]];
    }
}

-(void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error{
    [self setLeaderboardValue:@"Error"];
}

-(void)setLeaderboardValue:(NSString *)string{
    ((UILabel *)[self.view.subviews objectAtIndex:4]).text = string;
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

-(void)dealloc{
    UIView *controllerView = self.view;
    [Helper releaseMutableContainer:&datas];
    [Helper removeSubviewsFromParent:&controllerView];
    settings = NULL;
    [super dealloc];
}

@end
